//---------------------------------------------------------------------------

#ifndef EdgeHistoryFormH
#define EdgeHistoryFormH
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
	TVirtualStringTree *VirtualStringTree;
	TButton *DisplayHistoryButton;
	TButton *DeleteStringButton;
	TButton *ClearTableButton;
	TButton *ExitButton;
	TLabel *StringInfoLabel;
	TComboBox *ChooseBrowser;
	TButton *ClearHistoryButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall DisplayHistoryButtonClick(TObject *Sender);
	void __fastcall VirtualStringTreeGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall VirtualStringTreeNodeClick(TBaseVirtualTree *Sender, const THitInfo &HitInfo);
	void __fastcall ClearTableButtonClick(TObject *Sender);
	void __fastcall ExitButtonClick(TObject *Sender);
	void __fastcall DeleteStringButtonClick(TObject *Sender);
	void __fastcall ChooseBrowserSelect(TObject *Sender);
	void __fastcall ClearHistoryButtonClick(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
