//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	TLabel *Label1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TLabel *Label2;
	TVirtualStringTree *VirtualStringTree1;
	void __fastcall VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall VirtualStringTree1AddToSelection(TBaseVirtualTree *Sender, PVirtualNode Node);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
typedef struct
{
		int id;
		UnicodeString prefix;
		UnicodeString host;
		int frecency;
} TableStruct;
#endif
