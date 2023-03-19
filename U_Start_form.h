//---------------------------------------------------------------------------

#ifndef U_Start_formH
#define U_Start_formH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class TStart_form : public TForm
{
__published:	// IDE-managed Components
	TButton *Продолжить;
	TLabel *Label1;
	TImage *Image1;
	TImage *Image2;
	TLabel *Label2;
	TLabel *Label3;
	void __fastcall ПродолжитьClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TStart_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TStart_form *Start_form;
//---------------------------------------------------------------------------
#endif
