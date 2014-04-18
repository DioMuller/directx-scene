////////////////////////////////////
// Parameters
////////////////////////////////////
uniform extern float4x4 World;
uniform extern float4x4 View;
uniform extern float4x4 Projection;

uniform extern float Time;
uniform extern float3 Source;

////////////////////////////////////
// Structs
////////////////////////////////////

struct OutputVS
{
	float4 posH : POSITION0;
	float4 color : COLOR0;
};

////////////////////////////////////
// Variables
////////////////////////////////////
// Amplitude
static float a = 1.0f;

// Wave lenght
static float k = 0.1f;

// Angular frequency
static float w = 2.0f;

////////////////////////////////////
// Helper Functions
////////////////////////////////////

float RadialWaves(float3 position)
{
	//Calculamos a dist�ncia entre a origem das ondas e a posi��o do v�rtice
	float d = distance(Source.xz, position.xz);

	//Calculamos a altura da onda
	return a*sin(k*d - Time*w);
}

float4 GetIntensityFromHeight(float y)
{
	float c = y / a + 2;
	return float4(c, c, c, 1.0f);
}

////////////////////////////////////
// Vertex Shader
////////////////////////////////////
OutputVS TransformVS(float3 posL : POSITION0, float4 color : COLOR0)
{
	float4x4 wvp = mul(World, mul(View, Projection));

	// Zera nossa sa�da
	OutputVS outVS = (OutputVS)0;

	posL.y = posL.y + RadialWaves(posL);

	// Transforma no espa�o homog�neo
	outVS.posH = mul(float4(posL, 1.0f), wvp);
	outVS.color = color;

	return outVS;
}


OutputVS WaveVS(float3 posL : POSITION0, float4 color : COLOR0)
{
	OutputVS outVS = (OutputVS)0;
	float4x4 wvp = mul(World, mul(View, Projection));

	//Altera a posi��o y de acordo com a onda.
	posL.y = RadialWaves(posL);

	//Altera a cor de acordo com a altura
	outVS.color = color * GetIntensityFromHeight(posL.y);

	//Transforma a posi��o
	outVS.posH = mul(float4(posL, 1.0f), wvp);
	return outVS;
}

////////////////////////////////////
// Pixel Shader
////////////////////////////////////
float4 TransformPS(OutputVS inVS) : COLOR
{
	return inVS.color;
}

float4 WavePS(OutputVS inVS) : COLOR
{
	return inVS.color;
}


////////////////////////////////////
// Techniques
////////////////////////////////////
technique TransformTech
{
	pass P0
	{
		//Especificamos os shaders dessa passada
		vertexShader = compile vs_2_0 TransformVS();
		pixelShader = compile ps_2_0 TransformPS();
		//Especificamos os device states
		FillMode = Solid;
	}
}

technique WaveTech
{
	pass P0
	{
		//Especificamos os shaders dessa passada
		vertexShader = compile vs_2_0 WaveVS();
		pixelShader = compile ps_2_0 WavePS();
		//Especificamos os device states
		FillMode = Solid;
	}
}
