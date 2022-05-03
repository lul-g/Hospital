#include <iostream>
#include <vector>
#include <cstdio>
#include "User.cpp"

using namespace std;

///THE BASIC IDEA OF MY CODE IS:
///* GET METHOD CALL FROM USER
///* FIGURE OUT WHICH METHOD HAS BEEN CALLED USING SWITCH STATEMENTS
///* GO TO METHOD AND EXECUTE
        ///PATIENT CLASS HAS A CONSTRUCTOR THAT RECEIVES A VECTOR OF STRINGS AND FIGURES OUT WHAT TO SET WHAT TO (MIKE TO FIRSTNAME, 0 TO TREATED...)
        ///THEN THE GAME CAN BEGIN (ITS UPTO EACH METHOD FROM THEN ON)

 int main() {
     string methodCalled;
     User *user = new User();

     do {
         printf("%66s", "| 0 | QUIT AND CLEAR LOGGER FILE\n");
         printf("%69s", "|-1 | NO QUIT BUT LOGGER CLEAR FILE\n");
         printf("%65s", "|-2 | QUIT AND LOGGER SAVE FILE\n");
         printf("%67s", "|-3 | CLEAR SOME REPORT FROM FILE\n");
         printf("%-70s %s", "|1| ADD A PATIENT MANUALLY", "|6| PRINT OUT TREATED PATIENTS REPORT\n");
         printf("%-70s %s", "|2| ADD PATIENTS FROM FILE", "|7| FIND NEXT PATIENT TO BE TREATED\n");
         printf("%-70s %s", "|3| TREAT A PATIENT", "|8| TREAT ALL PATIENTS\n");
         printf("%-70s %s", "|4| PRINT OUT SINGLE PATIENT REPORT", "|9| PRINT PATIENT BY DOCTOR\n");
         printf("%-70s %s", "|5| PRINT OUT ALL PATIENTS REPORT", "|10| TURN ON DEBUG MODE\n");
//         printf("%67s", "|-4 | USER MANUAL-UNDERSTAND CODE\n");

         printf("\n%s", "PLEASE SELECT WHAT YOU WOULD LIKE TO DO FROM THE MENU ABOVE:");

         cin >> methodCalled;
         cout << endl;

         user->setAccess(methodCalled);
     }while(methodCalled != "0" && methodCalled != "-2");
 }







