//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "mmsystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x = 5; // pilka bedzie sie poruszac w lewo
int y = 5;  // pilka bedzie sie poruszac w gore
int bounces = 0; // ilosc odbic pi³ki
int level = 1;
int leftPlayerPoints = 0;
int rightPlayerPoints = 0;
AnsiString whichPlayer = "";

void  whoWon() {
    if (whichPlayer == "left")
        {
                Form1->LabelPoints->Visible = true;
                Form1->LabelPoints->Caption = " < Punkt dla gracza lewego ";
                leftPlayerPoints++;
                level++;
         }
        else if (whichPlayer == "right")
        {
                Form1->LabelPoints->Visible = true;
                Form1->LabelPoints->Caption = " Punkt dla gracza prawego > ";
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

  // if ( ball->Left + x > tlo->Left) x *= -1;
  // if ( ball->Top +x > tlo->Top) x *= -1;

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
            whoWon();
        }
  // odbicie od lewej paletki
   else if (ball->Left <= paddleLeft->Left + paddleLeft->Width &&  ball->Top + ball->Height/2 <= paddleLeft->Top + paddleLeft->Height &&
           ball->Top + ball->Height/2 >= paddleLeft->Top)
        {
          bounces++;
          whichPlayer = "left";
            //srodek paletki - pilka przyspiesza
               if (ball->Left <= paddleLeft->Left + paddleLeft->Width && ball->Top + ball->Height/2 <= paddleLeft->Top + 2/3*paddleLeft->Height &&
                        ball->Top + ball->Height/2 >= paddleLeft->Top + paddleLeft->Height/3)
                  {
                     x = -1.4*x;
                     y = 1.1*y;
                  } else x = -1.1*x;
        }
                        // odbicie od prawej paletki
   else if (ball->Left + ball->Width >= paddleRight->Left  && ball->Top + ball->Height/2 <= paddleRight->Top + paddleRight->Height &&
           ball->Top + ball->Height/2 >= paddleRight->Top)
        {
         bounces++;
         whichPlayer = "right";
                         //srodek paletki - pilka przyspiesza
               if (ball->Left <= paddleRight->Left + paddleRight->Width && ball->Top + ball->Height/2 <= paddleRight->Top + paddleRight->Height &&
                        ball->Top + ball->Height/2 >= paddleRight->Top + 2/3*paddleRight->Height)
                  {
                      x = -1.4*x;
                      y = 1.1*y;
                  } else  x = -1.1*x;
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
     TimerBall->Enabled = true;
     ball->Visible = true;

     Start->Visible = false;
     ButtomNewGame->Visible = false;
     ButtomNextLevel->Visible = false;
     LabelPoints->Visible = false;
     LabelBounces->Visible = false;
     LabelLevel->Visible = false;

     ball->Left = tlo->Width/2;
     ball->Top = tlo->Height/2;

}
//---------------------------------------------------------------------------


