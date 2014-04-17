uniform extern float4x4 World;
uniform extern float4x4 View;
uniform extern float4x4 Projection;

uniform extern float Time;
uniform extern float3 Source;

struct OutputVS
{
	float4 posH : POSITION0;
	float4 color : COLOR0;
};

// Amplitude
static float a = 2.0f;

// Wave lenght
static float k = 0.2f;

// Angular frequency
static float w = 4.0f;

// Vertex Shader
OutputVS TransformVS(float3 posL : POSITION0, float4 color : COLOR0)
{
	float4x4 wvp = mul(World, mul(View, Projection));

		// Zera nossa saída
		OutputVS outVS = (OutputVS)0;

	// Transforma no espaço homogêneo
	outVS.posH = mul(float4(posL, 1.0f), wvp);
	outVS.color = color;

	return outVS;
}

float RadialWaves(float3 position)
{
	//Calculamos a distância entre a origem das ondas e a posição do vértice
	float d = distance(Source.xz, position.xz);

	//Calculamos a altura da onda
	return a*sin(k*d - Time*w);
}

float4 GetIntensityFromHeight(float y)
{
	float c = y / (2.0f*a) + 0.5f;
	return float4(c, c, c, 1.0f);
}

OutputVS WaveVS(float3 posL : POSITION0, float4 color : COLOR0)
{
	OutputVS outVS = (OutputVS)0;
	float4x4 wvp = mul(World, mul(View, Projection));

		//Altera a posição y de acordo com a onda.
		posL.y = RadialWaves(posL);

	//Altera a cor de acordo com a altura
	outVS.color = color * GetIntensityFromHeight(posL.y);

	//Transforma a posição
	outVS.posH = mul(float4(posL, 1.0f), wvp);
	return outVS;
}

// Pixel Shader
float4 TransformPS(OutputVS inVS) : COLOR
{
	return inVS.color * float4(1.1f, 1.2f, 1.5f, 1.0f);
}

float4 TransformPS2(OutputVS inVS) : COLOR
{
	return float4(0.0f, 0.0f, 0.0f, 1.0f);
}

float4 WavePS(OutputVS inVS) : COLOR
{
	return inVS.color;
}


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
	pass P1
	{
		//Especificamos os shaders dessa passada
		vertexShader = compile vs_2_0 TransformVS();
		pixelShader = compile ps_2_0 TransformPS2();
		//Especificamos os device states
		FillMode = Wireframe;
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
