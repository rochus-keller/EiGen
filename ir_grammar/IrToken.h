#ifndef AOTOKEN_H
#define AOTOKEN_H

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

#include <QString>
#include <QPair>
#include <IrTokenType.h>

namespace Ir
{
    struct RowCol
    {
        enum { ROW_BIT_LEN = 19, COL_BIT_LEN = 32 - ROW_BIT_LEN - 1, MSB = 0x80000000 };
        uint d_row : ROW_BIT_LEN; // supports 524k lines
        uint d_col : COL_BIT_LEN; // supports 4k chars per line
        uint unused : 1;
        RowCol():d_row(0),d_col(0),unused(0) {}
        RowCol( quint32 row, quint32 col );
        bool setRowCol( quint32 row, quint32 col );
        bool isValid() const { return d_row > 0 && d_col > 0; } // valid lines and cols start with 1; 0 is invalid
        quint32 packed() const { return ( d_row << COL_BIT_LEN ) | d_col | MSB; }
        static bool isPacked( quint32 rowCol ) { return rowCol & MSB; }
        static quint32 unpackCol(quint32 rowCol ) { return rowCol & ( ( 1 << COL_BIT_LEN ) -1 ); }
        static quint32 unpackCol2(quint32 rowCol ) { return isPacked(rowCol) ? unpackCol(rowCol) : 1; }
        static quint32 unpackRow(quint32 rowCol ) { return ( ( rowCol & ~MSB ) >> COL_BIT_LEN ); }
        static quint32 unpackRow2(quint32 rowCol ) { return isPacked(rowCol) ? unpackRow(rowCol) : rowCol; }
        quint32 line() const { return d_row; }
        bool operator==( const RowCol& rhs ) const { return d_row == rhs.d_row && d_col == rhs.d_col; }
    };

    struct Loc : public RowCol
    {
        Loc( quint32 row, quint32 col, const QString& f ):RowCol( row, col ),d_file(f) {}
        Loc( const RowCol& r, const QString& f):RowCol(r),d_file(f) {}
        QString d_file;
    };

    typedef QPair<RowCol,RowCol> Range;
    typedef QList<Range> Ranges;
    struct FilePos
    {
        RowCol d_pos;
        QString d_filePath;
        FilePos(RowCol pos = RowCol(), const QString& path = QString()):d_pos(pos),d_filePath(path){}
    };
    struct Token
    {
#ifdef _DEBUG
        union
        {
        int d_type; // TokenType
        TokenType d_tokenType;
        };
#else
        quint16 d_type; // TokenType
#endif
        quint16 d_len;

        uint d_lineNr : RowCol::ROW_BIT_LEN; // supports 524k lines
        uint d_colNr : RowCol::COL_BIT_LEN; // supports 4k chars per line
        uint d_double : 1;     // originally unused, now set if floating point mantissa or exponent require double precision

        QByteArray d_val;
        QString d_sourcePath;
        Token(quint16 t = Tok_Invalid, quint32 line = 0, quint16 col = 0, quint16 len = 0, const QByteArray& val = QByteArray() ):
            d_type(t),d_lineNr(line),d_colNr(col),d_len(len),d_val(val),d_double(0){}
        bool isValid() const;
        bool isEof() const;
        const char* getName() const;
        const char* getString() const;
        RowCol toRowCol() const { return RowCol(d_lineNr,d_colNr); }
        Loc toLoc() const { return Loc(d_lineNr,d_colNr,d_sourcePath); }
    };

    typedef QList<Token> TokenList;
}

#endif // AOTOKEN_H
