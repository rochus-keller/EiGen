#include <stdio.h>
#include <stdlib.h>

int main()
{
   FILE *f = fopen("fred.txt", "w");
   fwrite("hello\nhello\n", 1, 12, f);
   fclose(f);

   char freddy[7];
   f = fopen("fred.txt", "r");
   if (fread(freddy, 1, 6, f) != 6)
      printf("couldn't read fred.txt\n");

   freddy[6] = '\0';
   fclose(f);

   printf("%s", freddy);

   int InChar;
   char ShowChar;
   f = fopen("fred.txt", "r");
   while ( (InChar = fgetc(f)) != EOF)
   {
      ShowChar = InChar;
      if (ShowChar < ' ')
         ShowChar = '.';

      printf("ch: %d '%c'\n", InChar, ShowChar);
   }
   fclose(f);
   
   printf("rand=%d\n",rand());
   printf("rand=%d\n",rand());
   printf("rand=%d\n",rand());
   printf("rand=%d\n",rand());

#if 0
   // TODO: FILE functions from the ECS standard lib apparently not compatible with Newlib
   // fgetc defined in ECS lib and used above works, getc used below from libc.so.6 doesnt
   
   #if 0
   putchar('H');
   putchar('i');
   putchar('!');
   putchar('\n');
   #endif

   f = fopen("fred.txt", "r");
   while ( (InChar = getc(f)) != EOF)
   {
      ShowChar = InChar;
      if (ShowChar < ' ')
         ShowChar = '.';

      printf("ch: %d '%c'\n", InChar, ShowChar);
   }
   fclose(f);

   f = fopen("fred.txt", "r");
   while (fgets(freddy, sizeof(freddy), f) != NULL)
      printf("x: %s", freddy);

   fclose(f);
   #endif

   return 0;
}

/* vim: set expandtab ts=4 sw=3 sts=3 tw=80 :*/
