struct {
   unsigned int male : 1;
   unsigned int age : 5;
   char name[8];
} person;

// works also with signed int and age -13
// works also with unsigned short and unsigned char

int main() {

   person.age = 13;
   person.male = 1;
   
   const int res = person.age == 13 && person.male;

   return !res;
}
