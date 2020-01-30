//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "mmsystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x = 5; int y = 5;
int bounces = 0; // ilosc odbic pi³ki
int level = 1;
int leftPlayerPoints = 0;
int rightPlayerPoints = 0;
AnsiString whichPlayer = "";

void settingParameters(){

        Form1->paddleLeft->Left = Form1->tlo->Left + 20;
        Form1->paddleLeft->Top = Form1->tlo->Height/2 - Form1->paddleLeft->Height/2;
        Form1->paddleRight->Left = Form1->tlo->Width - Form1->paddleRight->Width - 20;
        Form1->paddleRight->Top = Form1->tlo->Height/2 - Form1->paddleRight->Height/2;

        Form1->ball->Left = Form1->tlo->Width/2;
        Form1->ball->Top = Form1->tlo->Height/2;

        Form1->ButtomNewGame->Left = Form1->tlo->Width/2 - Form1->ButtomNewGame->Width/2;
        Form1->ButtomNextLevel->Left = Form1->tlo->Width/2 -Form1->ButtomNextLevel->Width/2;
        Form1->LabelBounces->Left = Form1->tlo->Width/2 -Form1->LabelBounces->Width/2;
        Form1->LabelLevel->Left = Form1->tlo->Width/2 -Form1->LabelLevel->Width/2;
        Form1->LabelPoints->Left = Form1->tlo->Width/2 -Form1->LabelPoints->Width/2;

}

void  whoWon() {
    if (whichPlayer == "left")
        {
                Form1->LabelPoints->Visible = true;
                Form1->LabelPoints->Caption = " < Punkt dla gracza lewego. Zaczyna gracz lewy. ";
                x = 5; y = 5;
                leftPlayerPoints++;
                level++;
         }
        else if (whichPlayer == "right")
        {
                Form1->LabelPoints->Visible = true;
                Form1->LabelPoints->Caption = " Punkt dla gracza prawego. Zaczyna gracz prawy. > ";
                x = -5; y = -5;
                rightPlayerPoints++;
                level++;
        }

         Form1->LabelLevel->Visible = true;
         Form1->LabelLevel->Caption = IntToStr(leftPlayerPoints) + " : " + IntToStr(rightPlayerPoints);
         Form1->LabelBounces->Visible = true;
         Form1-> LabelBounces->Caption = "Ilosc odbic: " + IntToStr(bounces);
         Form1-> ButtomNextLevel->Visible = true;
         Form1-> ButtomNewGame->Visible = true;

}



//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerBallTimer(TObject *Sender)
{
   ball->Left += x;   //przesuniêcie pi³ki
   ball->Top += y;

   //odbij od górnej sciany
   if ( ball->Top-5 <= tlo->Top) y = -y;

   //odbij od dolnej sciany
  if ( ball->Top + ball->Height-5 >= tlo->Height ) y = -y;

  // skucie
   if  (( ball->Left <= paddleLeft->Left  &&
       ( ball->Top + ball->Height/2 < paddleLeft->Top || ball->Top + ball->Height/2 > paddleLeft->Top + paddleLeft->Height )) ||
       ( ball->Left + ball->Width > paddleRight->Left + paddleRight->Width &&
       ( ball->Top + ball->Height/2 < paddleRight->Top || ball->Top + ball->Height/2 > paddleRight->Top + paddleRight->Height )))
        {
            TimerBall->Enabled = false;
            ball->Visible = false;
            sndPlaySound("snd/koniec.wav",SND_ASYNC);
            whoWon();
        }
  // odbicie od lewej paletki
   else if (ball->Left < paddleLeft->Left + paddleLeft->Width && ball->Top + ball->Height/2 <= paddleLeft->Top + paddleLeft->Height &&
           ball->Top + ball->Height/2 >= paddleLeft->Top)
        {
          sndPlaySound("snd/odbicie.wav",SND_ASYNC);
          bounces++;
          whichPlayer = "left";
            //srodek paletki - pilka przyspiesza
               if (ball->Left <= paddleLeft->Left + paddleLeft->Width && ball->Top + ball->Height/2 <= paddleLeft->Top + 2 * paddleLeft->Height/3 &&
                        ball->Top + ball->Height/2 >= paddleLeft->Top + paddleLeft->Height/3)
                  {
                     x = -1.4*x;
                     y = 1.1*y;
                  } else x = -1.2*x;
        }
                        // odbicie od prawej paletki
   else if (ball->Left + ball->Width >= paddleRight->Left  && ball->Top + ball->Height/2 <= paddleRight->Top + paddleRight->Height &&
           ball->Top + ball->Height/2 >= paddleRight->Top)
        {
         sndPlaySound("snd/odbicie.wav",SND_ASYNC);
         bounces++;
         whichPlayer = "right";
                         //srodek paletki - pilka przyspiesza
               if (ball->Left <= paddleRight->Left + paddleRight->Width && ball->Top + ball->Height/2 <= paddleRight->Top + 2 * paddleRight->Height/3 &&
                        ball->Top + ball->Height/2 >= paddleRight->Top + paddleRight->Height/3)
                  {
                      x = -1.4*x;
                      y = 1.1*y;
                  } else  x = -1.2*x;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddleLeftUpTimer(TObject *Sender)
{
    if ( paddleLeft->Top > 10) paddleLeft->Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddleLeftDownTimer(TObject *Sender)
{
   if ( paddleLeft->Top + paddleLeft->Height < tlo->Height-10) paddleLeft->Top += 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddleRightUpTimer(TObject *Sender)
{
     if ( paddleRight->Top > 10)  paddleRight->Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddleRightDownTimer(TObject *Sender)
{
     if ( paddleRight->Top + paddleRight->Height < tlo->Height-10) paddleRight->Top += 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key == VK_UP) paddleRightUp->Enabled = true;
    if (Key == VK_DOWN) paddleRightDown->Enabled = true;
    if (Key == 'A') paddleLeftUp->Enabled = true;
    if (Key == 'Z') paddleLeftDown->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key == VK_UP) paddleRightUp->Enabled = false;
    if (Key == VK_DOWN) paddleRightDown->Enabled = false;
    if (Key == 'A') paddleLeftUp->Enabled = false;
    if (Key == 'Z') paddleLeftDown->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtomNewGameClick(TObject *Sender)
{



     if (level > 1){
     if (Application->MessageBox("Czy na pewno chcesz rozpocz¹æ now¹ grê?","PotwierdŸ",
      MB_YESNO | MB_ICONQUESTION) == IDYES){

     settingParameters() ;
     leftPlayerPoints = 0;
     rightPlayerPoints = 0;
     level = 1;
     bounces = 0;

     TimerBall->Enabled = true;
     ball->Visible = true;

     Start->Visible = false;
     ButtomNewGame->Visible = false;
     ButtomNextLevel->Visible = false;
     LabelPoints->Visible = false;
     LabelBounces->Visible = false;
     LabelLevel->Visible = false;
     }
     }   else if (level = 1){

     settingParameters() ;
     leftPlayerPoints = 0;
     rightPlayerPoints = 0;
     level = 1;
     bounces = 0;

     TimerBall->Enabled = true;
     ball->Visible = true;

     Start->Visible = false;
     ButtomNewGame->Visible = false;
     ButtomNextLevel->Visible = false;
     LabelPoints->Visible = false;
     LabelBounces->Visible = false;
     LabelLevel->Visible = false;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtomNextLevelClick(TObject *Sender)
{
     settingParameters();

     if (whichPlayer == "left")        ball->Left = paddleLeft->Left + Form1->paddleLeft->Width;
     else if (whichPlayer == "right")  ball->Left = paddleRight->Left - Form1->ball->Width;

     TimerBall->Enabled = true;
     ball->Visible = true;

     Start->Visible = false;
     ButtomNewGame->Visible = false;
     ButtomNextLevel->Visible = false;
     LabelPoints->Visible = false;
     LabelBounces->Visible = false;
     LabelLevel->Visible = false;


}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
      ShowMessage("Witaj w grze PingPong.\n\n"
                  "Lewy gracz steruje wciskaj¹c klawisze A oraz Z.\n"
                  "Prawy gracz steruje wciskaj¹c strza³ki do góry i w dó³.\n\n"
                  "Dla urozmaicenia zabawy:\n"
                  "Kiedy odbijesz pi³kê na œrodku paletki zmienisz jej k¹t odcicia i pi³ka przyœpieszy.\n"
                  "Im d³u¿ej odbijasz, tym pi³ka szybciej przemieszcza siê.\n"
                  "Mo¿esz dowolnie zmieniaæ pole gry.\n"
                  "Nastêpn¹ rundê rozpoczyna gracz zdobywaj¹cy punkt.\n"

      );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
     if (Application->MessageBox("Czy na pewno chcesz zakoñczyæ grê?","PotwierdŸ",
      MB_YESNO | MB_ICONQUESTION) == IDYES)
      Action = caFree;
     else Action = caNone;
}
//---------------------------------------------------------------------------

