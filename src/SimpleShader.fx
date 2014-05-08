////////////////////////////////////
// Parameters
////////////////////////////////////
uniform extern float4x4 World;
uniform extern float4x4 View;
uniform extern float4x4 Projection;

uniform extern float Time;
uniform extern float3 Source;
uniform extern float4 MeshPosition;

uniform extern texture Texture;
uniform extern texture AlphaTexture;

////////////////////////////////////
// Samplers
////////////////////////////////////
sampler TextureSampler = sampler_state
{
	Texture = <Texture>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

////////////////////////////////////
// Structs
////////////////////////////////////

struct OutputVS
{
	float4 posH : POSITION0;
	float2 textureCoord : TEXCOORD0;
	float4 color : COLOR0;
};

////////////////////////////////////
// Variables
////////////////////////////////////
// Amplitude
static float a = 0.5f;

// Wave lenght
static float k = 15.0f;

// Angular frequency
static float w = 1.0f;

static float skyspeed = 0.03f;

////////////////////////////////////
// Helper Functions
////////////////////////////////////

float RadialWaves(float3 position)
{
	//Calculamos a distância entre a origem das ondas e a posição do vértice
	float d = distance(Source.xz, position.xz);

	//Calculamos a altura da onda
	return a*sin(k*d - Time*w);
}

float MeshMovement(float3 position)
{
	//Calculamos a distância entre a origem das ondas e a posição do vértice
	float d = distance(Source.xz, MeshPosition.xz);

	//Calculamos a altura da onda
	return a*sin(k*d - Time*w);
}

float4 GetIntensityFromHeight(float y)
{
	float c = y / a + 2;
	return float4( c, c, c, 1.0f);
}

////////////////////////////////////
// Vertex Shader
////////////////////////////////////
OutputVS TransformVS(float3 posL : POSITION0, float2 texCoord : TEXCOORD0, float4 color : COLOR0)
{
	float4x4 wvp = mul(World, mul(View, Projection));

	// Zera nossa saída
	OutputVS outVS = (OutputVS)0;

	posL.y = posL.y + MeshMovement(posL) + 0.2;

	// Transforma no espaço homogêneo
	outVS.posH = mul(float4(posL, 1.0f), wvp);
	outVS.color = color;
	outVS.textureCoord = texCoord;

	return outVS;
}

OutputVS TexturedVS(float3 posL : POSITION0, float2 texCoord : TEXCOORD0, float4 color : COLOR0)
{
	float4x4 wvp = mul(World, mul(View, Projection));

		// Zera nossa saída
		OutputVS outVS = (OutputVS)0;

	posL.y = posL.y + MeshMovement(posL) + 0.2;

	// Transforma no espaço homogêneo
	outVS.posH = mul(float4(posL, 1.0f), wvp);
	outVS.color = color;
	outVS.textureCoord = texCoord;

	return outVS;
}

OutputVS WaveVS(float3 posL : POSITION0, float2 texCoord : TEXCOORD0, float4 color : COLOR0)
{
	OutputVS outVS = (OutputVS)0;
	float4x4 wvp = mul(World, mul(View, Projection));

	//Altera a posição y de acordo com a onda.
	posL.y = RadialWaves(posL);

	//Altera a cor de acordo com a altura
	outVS.color = color * GetIntensityFromHeight(posL.y);

	//Transforma a posição
	outVS.posH = mul(float4(posL, 1.0f), wvp);

	outVS.textureCoord = texCoord;
	return outVS;
}

OutputVS TerrainVS(float3 posL : POSITION0, float2 texCoord : TEXCOORD0, float4 color : COLOR0)
{
	float4x4 wvp = mul(World, mul(View, Projection));

	// Zera nossa saída
	OutputVS outVS = (OutputVS)0;

	outVS.color = float4(color.r / abs(posL.y / 2), color.g, color.b, color.a);

	// Transforma no espaço homogêneo
	outVS.posH = mul(float4(posL, 1.0f), wvp);

	outVS.textureCoord = texCoord;

	return outVS;
}

OutputVS SimpleVS(float3 posL : POSITION0, float2 texCoord : TEXCOORD0, float4 color : COLOR0)
{
	float4x4 wvp = mul(World, mul(View, Projection));

	// Zera nossa saída
	OutputVS outVS = (OutputVS)0;

	outVS.color = color;

	// Transforma no espaço homogêneo
	outVS.posH = mul(float4(posL, 1.0f), wvp);

	outVS.textureCoord = texCoord;

	return outVS;
}

OutputVS SkyVS(float3 posL : POSITION0, float2 texCoord : TEXCOORD0, float4 color : COLOR0)
{
	float4x4 wvp = mul(World, mul(View, Projection));

	// Zera nossa saída
	OutputVS outVS = (OutputVS)0;

	outVS.color = color;

	// Transforma no espaço homogêneo
	outVS.posH = mul(float4(posL, 1.0f), wvp);

	outVS.textureCoord = float2(texCoord.x + Time * skyspeed, texCoord.y);

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
	return float4(inVS.color.r, inVS.color.g, inVS.color.b, 0.5f);
}

float4 TerrainPS(OutputVS inVS) : COLOR
{
	return float4(tex2D(TextureSampler, inVS.textureCoord).rgb, 1.0f);
}

float4 TexturedPS(OutputVS inVS) : COLOR
{
	return float4(tex2D(TextureSampler, inVS.textureCoord).rgba);
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

technique TerrainTech
{
	pass P0
	{
		//Especificamos os shaders dessa passada
		vertexShader = compile vs_2_0 TerrainVS();
		pixelShader = compile ps_2_0 TerrainPS();
		//Especificamos os device states
		FillMode = Solid;
	}
}

technique WaveTech
{
	pass P0
	{
		// Shaders
		vertexShader = compile vs_2_0 WaveVS();
		pixelShader = compile ps_2_0 WavePS();
		// Device States
		// Fill Mode
		FillMode = Solid;
		// Transparency
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		BlendOp = Add;
	}
}

technique TexturedTech
{
	pass P0
	{
		// Shaders
		vertexShader = compile vs_2_0 TexturedVS();
		pixelShader = compile ps_2_0 TexturedPS();
		// Device States
		FillMode = Solid;
	}
}

technique FixedTech
{
	pass P0
	{
		// Shaders
		vertexShader = compile vs_2_0 SimpleVS();
		pixelShader = compile ps_2_0 TexturedPS();
		// Device States
		FillMode = Solid;
	}
}

technique SkyTech
{
	pass P0
	{
		// Shaders
		vertexShader = compile vs_2_0 SkyVS();
		pixelShader = compile ps_2_0 TexturedPS();
		// Device States
		FillMode = Solid;
	}
}
technique CharacterTech
{
	pass P0
	{
		// Shaders
		vertexShader = compile vs_2_0 TransformVS();
		pixelShader = compile ps_2_0 TexturedPS();
		// Device States
		FillMode = Solid;
		AlphaTestEnable = true;
		AlphaFunc = GreaterEqual;
		AlphaRef = 200;
	}
}

technique BillboardTech
{
	pass P0
	{
		// Shaders
		vertexShader = compile vs_2_0 SimpleVS();
		pixelShader = compile ps_2_0 TexturedPS();
		// Device States
		FillMode = Solid;
		AlphaTestEnable = true;
		AlphaFunc = GreaterEqual;
		AlphaRef = 200;
	}
}