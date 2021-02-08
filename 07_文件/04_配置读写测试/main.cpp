#include "global.h"
#include "hTool.h"
#include "hTest.h"
#include "hConfig.h"
#include "test.h"

using namespace std;
TEST_INIT() {}

TEST(æ≤Ã¨∂•µ„ Ù–‘)
{
	StaticVertexAttribCfg cfg = StaticVertexAttribCfg("StaticVertexAttribCfg.yml");
	cfg.loadCfg();
	Debug(cout, cfg);
}

TEST_MAIN()