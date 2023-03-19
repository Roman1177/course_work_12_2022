//---------------------------------------------------------------------------

#ifndef U_Load_formH
#define U_Load_formH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TLoad_form : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
private:	// User declarations
public:		// User declarations
	__fastcall TLoad_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLoad_form *Load_form;
//---------------------------------------------------------------------------
#endif
