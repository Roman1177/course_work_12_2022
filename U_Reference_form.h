//---------------------------------------------------------------------------

#ifndef U_Reference_formH
#define U_Reference_formH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TRef_form : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TLabel *Label_sheet_1;
	TLabel *Label1;
	TTabSheet *TabSheet2;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:	// User declarations
public:		// User declarations
	__fastcall TRef_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRef_form *Ref_form;
//---------------------------------------------------------------------------
#endif
