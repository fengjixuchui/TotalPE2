#pragma once

#include "ViewBase.h"
#include <VirtualListView.h>
#include <PEFile.h>
#include <CustomSplitterWindow.h>
#include "HexView.h"

class CResourcesView :
	public CViewBase<CResourcesView>,
	public CVirtualListView<CResourcesView> {
public:
	CResourcesView(IMainFrame* frame, const PEFile& pe);

	CString GetColumnText(HWND, int row, int col) const;
	int GetRowImage(HWND, int row, int) const;
	void DoSort(SortInfo const* si);
	void OnStateChanged(HWND, int from, int to, DWORD oldState, DWORD newState);

	void UpdateUI(bool first = false);

	BEGIN_MSG_MAP(CResourcesView)
		MESSAGE_HANDLER(CFindReplaceDialog::GetFindReplaceMsg(), OnFind)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		CHAIN_MSG_MAP(CVirtualListView<CResourcesView>)
		CHAIN_MSG_MAP(BaseFrame)
	ALT_MSG_MAP(1)
		COMMAND_ID_HANDLER(ID_EDIT_COPY, OnCopy)
	END_MSG_MAP()

private:
	enum ColumnType {
		Name, Size, Type, RVA, Language,
	};

	CString GetTitle() const override;

	void BuildItems();

	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCopy(WORD, WORD, HWND, BOOL&) const;
	LRESULT OnFind(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	CListViewCtrl m_List;
	CCustomHorSplitterWindow m_Splitter;
	std::vector<FlatResource> m_Resources;
	PEFile const& m_PE;
	CHexView m_HexView;
};