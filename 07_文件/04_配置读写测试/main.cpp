#include "global.h"

#include "vgl.h"
#include "vapp.h"

#include "hTool.h"
#include "hTest.h"
#include "hConfig.h"
#include "test.h"

using namespace std;
TEST_INIT() {}

TEST(��̬��������)
{
	StaticVertexAttribCfg cfg = StaticVertexAttribCfg("StaticVertexAttribCfg.yml");
	cfg.loadCfg();
	Debug(cout, cfg) << endl;
}

TEST_MAIN()