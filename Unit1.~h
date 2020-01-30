//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <MPlayer.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TShape *tlo;
        TImage *ball;
        TTimer *TimerBall;
        TImage *paddleLeft;
        TImage *paddleRight;
        TTimer *paddleLeftUp;
        TTimer *paddleLeftDown;
        TTimer *paddleRightUp;
        TTimer *paddleRightDown;
        TLabel *Start;
        TButton *ButtomNewGame;
        TLabel *LabelPoints;
        TLabel *LabelBounces;
        TLabel *LabelLevel;
        TButton *ButtomNextLevel;
        TMediaPlayer *MediaPlayer1;
        void __fastcall TimerBallTimer(TObject *Sender);
        void __fastcall paddleLeftUpTimer(TObject *Sender);
        void __fastcall paddleLeftDownTimer(TObject *Sender);
        void __fastcall paddleRightUpTimer(TObject *Sender);
        void __fastcall paddleRightDownTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall ButtomNewGameClick(TObject *Sender);
        void __fastcall ButtomNextLevelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
