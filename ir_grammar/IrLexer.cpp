/*
* Copyright 2023 Rochus Keller <mailto:me@rochus-keller.ch>
*
* This file is part of the ActiveOberon parser/navigator project.
*
* The following is the license that applies to this copy of the
* file. For a license to use the file under conditions
* other than those described here, please email to me@rochus-keller.ch.
*
* GNU General Public License Usage
* This file may be used under the terms of the GNU General Public
* License (GPL) versions 2.0 or 3.0 as published by the Free Software
* Foundation and appearing in the file LICENSE.GPL included in
* the packaging of this file. Please review the following information
* to ensure GNU General Public Licensing requirements will be met:
* http://www.fsf.org/licensing/licenses/info/GPLv2.html and
* http://www.gnu.org/copyleft/gpl.html.
*/

#include "IrLexer.h"
#include <QBuffer>
#include <QFile>
#include <QIODevice>
#include <QtDebug>
using namespace Ir;

QHash<QByteArray,QByteArray> Lexer::d_symbols;

Lexer::Lexer(QObject *parent) : QObject(parent),
    d_lastToken(Tok_Invalid),d_lineNr(0),d_colNr(0),d_in(0),
    d_ignoreComments(true), d_packComments(true)
{

}

void Lexer::setStream(QIODevice* in, const QString& sourcePath)
{
    if( in == 0 )
        setStream( sourcePath );
    else
    {
        d_in = in;
        d_lineNr = 0;
        d_colNr = 0;
        d_sourcePath = sourcePath;
        d_lastToken = Tok_Invalid;
    }
}

bool Lexer::setStream(const QString& sourcePath)
{
    QIODevice* in = 0;

    QFile* file = new QFile(sourcePath, this);
    if( !file->open(QIODevice::ReadOnly) )
    {
        delete file;
        return false;
    }
    in = file;

     // else
    setStream( in, sourcePath );
    return true;
}

Token Lexer::nextToken()
{
    Token t;
    if( !d_buffer.isEmpty() )
    {
        t = d_buffer.first();
        d_buffer.pop_front();
    }else
        t = nextTokenImp();
    if( t.d_type == Tok_Comment && d_ignoreComments )
        t = nextToken();
    return t;
}

Token Lexer::peekToken(quint8 lookAhead)
{
    Q_ASSERT( lookAhead > 0 );
    while( d_buffer.size() < lookAhead )
        d_buffer.push_back( nextTokenImp() );
    return d_buffer[ lookAhead - 1 ];
}

QList<Token> Lexer::tokens(const QString& code)
{
    return tokens( code.toLatin1() );
}

QList<Token> Lexer::tokens(const QByteArray& code, const QString& path)
{
    QBuffer in;
    in.setData( code );
    in.open(QIODevice::ReadOnly);
    setStream( &in, path );

    QList<Token> res;
    Token t = nextToken();
    while( t.isValid() )
    {
        res << t;
        t = nextToken();
    }
    return res;
}

QByteArray Lexer::getSymbol(const QByteArray& str)
{
    if( str.isEmpty() )
        return str;
    QByteArray& sym = d_symbols[str];
    if( sym.isEmpty() )
        sym = str;
    return sym;
}

Token Lexer::nextTokenImp()
{
    if( d_in == 0 )
        return token(Tok_Eof);
    skipWhiteSpace();

    while( d_colNr >= d_line.size() )
    {
        if( d_in->atEnd() )
        {
            Token t = token( Tok_Eof, 0 );
            if( d_in->parent() == this )
                d_in->deleteLater();
            return t;
        }
        nextLine();
        skipWhiteSpace();
    }
    Q_ASSERT( d_colNr < d_line.size() );
    while( d_colNr < d_line.size() )
    {
        const char ch = quint8(d_line[d_colNr]);

        if( ch == '"' )
            return string();
        else if( ::isalpha(ch) || ch == '_' || ch == '.' || ch == '$' || ch == ':' )
            return ident();
        else if( ::isdigit(ch) )
            return number();
        // else
        int pos = d_colNr;
        TokenType tt = tokenTypeFromString(d_line,&pos);

        if( tt == Tok_Invalid || pos == d_colNr )
            return token( Tok_Invalid, 1, QString("unexpected character '%1' %2").arg(char(ch)).arg(int(ch)).toUtf8() );
        else if( tt == Tok_Semi )
        {
            const int len = d_line.size() - d_colNr;
            return token( Tok_Comment, len, d_line.mid(d_colNr,len) );
        }
        else {
            const int len = pos - d_colNr;
            return token( tt, len, d_line.mid(d_colNr,len) );
        }
    }
    Q_ASSERT(false);
    return token(Tok_Invalid);
}

int Lexer::skipWhiteSpace()
{
    const int colNr = d_colNr;
    while( d_colNr < d_line.size() && ::isspace( d_line[d_colNr] ) )
        d_colNr++;
    return d_colNr - colNr;
}

void Lexer::nextLine()
{
    d_colNr = 0;
    d_lineNr++;
    d_line = d_in->readLine();

    if( d_line.endsWith("\r\n") )
        d_line.chop(2);
    else if( d_line.endsWith('\n') || d_line.endsWith('\r') || d_line.endsWith('\025') )
        d_line.chop(1);
}

int Lexer::lookAhead(int off) const
{
    if( int( d_colNr + off ) < d_line.size() )
    {
        return d_line[ d_colNr + off ];
    }else
        return 0;
}

Token Lexer::token(TokenType tt, int len, const QByteArray& val)
{
    QByteArray v = val;
    if( tt != Tok_Comment && tt != Tok_Invalid )
        v = getSymbol(v);
    Token t( tt, d_lineNr, d_colNr + 1, len, v );
    d_lastToken = t;
    d_colNr += len;
    t.d_sourcePath = d_sourcePath;
    return t;
}

Token Lexer::ident()
{
    int off = 1;
    while( true )
    {
        const char c = lookAhead(off);
        if( !QChar(c).isLetterOrNumber() && // QChar wegen möglichen Umlauten
                c != '_' && c != '.' && c != '$' && c != ':' )
            break;
        else
            off++;
    }
    const QByteArray str = d_line.mid(d_colNr, off );
    Q_ASSERT( !str.isEmpty() );
    int pos = 0;
    TokenType t = tokenTypeFromString( str, &pos );
    if( t != Tok_Invalid && pos != str.size() )
        t = Tok_Invalid;
    if( t != Tok_Invalid )
        return token( t, off );
    else
        return token( Tok_identifier, off, str );
}

static inline bool isHexDigit( char c )
{
    return ::isdigit(c) || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F' ||
            c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f';
}

static inline bool allDecimal( QByteArray str )
{
    for( int i = 0; i < str.size(); i++ )
    {
        if( !::isdigit(str[i]) )
            return false;
    }
    return true;
}

static inline bool allBinary( const QByteArray& str )
{
    for( int i = 0; i < str.size(); i++ )
    {
        const char c = str[i];
        if( !( c == '0' || c == '1' ) )
            return false;
    }
    return true;
}

static inline bool allOctal( const QByteArray& str )
{
    for( int i = 0; i < str.size(); i++ )
    {
        const char c = str[i];
        if( !( c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5'
               || c == '6' || c == '7' ) )
            return false;
    }
    return true;
}

Token Lexer::number()
{
    // binary_integer ::= '0b' bin_digits | bin_digits 'b'
    // octal_integer ::=  '0o' oct_digits | oct_digits 'o' | '0' oct_digits
    // decimal_integer ::='0d' dec_digits | dec_digits 'd' | dec_digits
    // hex_integer ::=    '0h' hex_digits | hex_digits 'h' | '0x' hex_digits
    // real ::=           dec_digits '.' [ dec_digits ] [ 'e' ['+'|'-'] dec_digits ]

    int off = 1;
    if( lookAhead(0) == '0' )
    {
        char c;
        switch( lookAhead(off++) )
        {
        case 'b':
            while( c = lookAhead(off), c == '0' || c == '1' ) off++;
            return token( Tok_binary_integer, off, d_line.mid(d_colNr, off ));
        case 'o':
            while( c = lookAhead(off), c >= '0' && c <= '7' ) off++;
            return token( Tok_octal_integer, off, d_line.mid(d_colNr, off ));
        case 'd':
            while( c = lookAhead(off), ::isdigit(c) ) off++;
            return token( Tok_decimal_integer, off, d_line.mid(d_colNr, off ));
        case 'h':
        case 'x':
            while( c = lookAhead(off), isHexDigit(c) ) off++;
            return token( Tok_hex_integer, off, d_line.mid(d_colNr, off ));
        case '.':
            off = 1;
            break;
        default:
            while( c = lookAhead(off), c >= '0' && c <= '7' ) off++;
            return token( Tok_octal_integer, off-1, d_line.mid(d_colNr, off-1 ));
        }
    } // else

    while( isHexDigit(lookAhead(off)) )
        off++;

    switch(lookAhead(off))
    {
    case 'b':
        if( allBinary(d_line.mid(d_colNr, off++ )) )
            return token( Tok_binary_integer, off, d_line.mid(d_colNr, off ));
        else
            return token(Tok_Invalid, off, "invalid binary integer");
    case 'o':
        if( allOctal(d_line.mid(d_colNr, off++ )) )
            return token( Tok_octal_integer, off, d_line.mid(d_colNr, off ));
        else
            return token(Tok_Invalid, off, "invalid octal integer");
    case 'd':
        if( allDecimal(d_line.mid(d_colNr, off++ )) )
            return token( Tok_decimal_integer, off, d_line.mid(d_colNr, off ));
        else
            return token(Tok_Invalid, off, "invalid decimal integer");
    case 'h':
        off++;
        return token( Tok_hex_integer, off, d_line.mid(d_colNr, off ));
    case '.':
        off++;
        if( lookAhead(off) != 'e' && !::isdigit(lookAhead(off)))
            return token( Tok_real, off, d_line.mid(d_colNr, off ));
        break;
    default:
        if( allDecimal(d_line.mid(d_colNr, off )) )
            return token( Tok_decimal_integer, off, d_line.mid(d_colNr, off ));
        else
            return token(Tok_Invalid, off, "invalid decimal integer");
    }

    char c;
    while( c = lookAhead(off), ::isdigit(c) )
        off++;

    if( lookAhead(off) != 'e' )
        return token( Tok_real, off, d_line.mid(d_colNr, off ));

    off++;
    if( lookAhead(off) == '+' || lookAhead(off) == '-' )
        off++;
    if( !::isdigit(lookAhead(off)) )
        return token(Tok_Invalid, off, "invalid real number");
    while( ::isdigit(lookAhead(off)) ) off++;
    return token( Tok_real, off, d_line.mid(d_colNr, off ));
}

Token Lexer::string()
{
    const char quote = lookAhead(0);
    int off = 1;
    while( true )
    {
        const char c = lookAhead(off);
        off++;
        if( c == quote )
            break;
        if( c == 0 )
            return token( Tok_Invalid, off, "non-terminated string" );
    }
    const QByteArray str = d_line.mid(d_colNr, off );
    return token( Tok_string, off, str );
}

