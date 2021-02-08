#pragma once

//æ≤Ã¨∂•µ„ Ù–‘
#if 0
BEG_CFGDATA(StaticVertexAttribCfg)
{
	std::string shaderName;
	GLuint vertLoc = 0;
	GLuint colorLoc = 0;
	GLfloat vertice[3][2] = {};
	GLfloat staticColor[3] = {};
	GLfloat colors[3][3] = {};
}
END_CFGDATA(StaticVertexAttribCfg, shaderName, vertLoc, colorLoc, vertice, staticColor, colors)
#else
BEG_CFGDATA(StaticVertexAttribCfg)
{
	std::string shaderName;
}
END_CFGDATA(StaticVertexAttribCfg, shaderName)

#endif
