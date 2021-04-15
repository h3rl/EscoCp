#include "CCallback.h"

const int barlength = 25;

HRESULT CCallback::OnProgress(ULONG ulProgress,
	ULONG ulProgressMax,
	ULONG ulStatusCode,
	LPCWSTR szStatusText)
{
    if (ulProgress > 0 && ulStatusCode == BINDSTATUS_DOWNLOADINGDATA)
    {
        float val = (float)ulProgress;
        float maxvalue = (float)ulProgressMax;

        float percent = val / maxvalue;

        int printbars = (int)min(barlength, roundf(barlength * percent));

        string ret = "[";
        for (int i = 0; i < barlength; i++)
        {
            if (printbars > 0) {
                ret += "=";
                printbars--;
            }
            else
            {
                ret += " ";
            }
        }
        ret += "]";

        percent = min(100, percent * 100);

        printf("\r%s %.*f%%", ret.c_str(), 1, percent);

        if (percent == 100.f) {
            printf("\n");
            running = false;
        }

        Sleep(100);//add a delay
    }
	return S_OK;
}