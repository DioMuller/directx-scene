uniform extern float4x4 World;
uniform extern float4x4 View;
uniform extern float4x4 Projection;

struct OutputVS
{
	float4 posH : POSITION0;
	float4 color : COLOR0;
};

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

// Pixel Shader
float4 TransformPS(OutputVS inVS) : COLOR
{
	return inVS.color * float4(1.1f, 1.2f, 1.5f, 1.0f);
}

float4 TransformPS2(OutputVS inVS) : COLOR
{
	return float4(0.0f, 0.0f, 0.0f, 1.0f);
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
