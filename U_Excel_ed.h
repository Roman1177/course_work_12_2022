//---------------------------------------------------------------------------

#ifndef U_Excel_edH
#define U_Excel_edH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TExcel_editor : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TStringGrid *StringGrid1;
	TButton *Button2;
	TOpenDialog *OpenDialog1;
	TSaveDialog *SaveDialog1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall StringGrid1SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall StringGrid1KeyPress(TObject *Sender, System::WideChar &Key);

private:	// User declarations
public:		// User declarations
	__fastcall TExcel_editor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TExcel_editor *Excel_editor;
//---------------------------------------------------------------------------
#endif
