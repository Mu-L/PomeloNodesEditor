// PomeloNodeEditor_External. RCSZ.
// Pomelo ImGui ��չ����ģ��.

#ifndef _POMELONODEEDITOR_EXTERNAL_H
#define _POMELONODEEDITOR_EXTERNAL_H

#include "pomelo_nodeeditor.h"

namespace Ext_EditorFile {

	class FileProcessing {
	public:
		/*
		* @param  const char*        (File Path)
		* @param  IODATA::NodesLines (save src data)
		* @return bool
		*/
		bool Save_NodesDataFile(
			StrText            File,
			IODATA::NodesExport Source
		);
		/*
		* @param  const char* (File Path)
		* @param  std::vector<IODATA::SaveNodeData>& (�����ʽ�ڵ�����)
		* @param  std::vector<IODATA::SaveLineData>& (�����ʽ��������)
		* @return bool 
		*/
		bool Read_NodesDataFile(
			StrText                            File, 
			std::vector<IODATA::SaveNodeData>& nodes,
			std::vector<IODATA::SaveLineData>& lines
		);
	};

	void NodesEditorFileMenu(PNE::EdiorGUI& editobj);
}

#endif