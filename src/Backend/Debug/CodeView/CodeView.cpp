#include "CodeView.h"

namespace Backend::Debug::CodeView
{
    CodeView::CodeView(OutputFormats::PE::PE& pe) :
        m_pe(pe)
    {
    }

    CodeView::~CodeView()
    {
    }
}