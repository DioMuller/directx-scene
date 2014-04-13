//==================================================================
// Efeito b�sico que simplesmente transforma a geometria do espa�o
// local para o homog�neo e deseja a geometria em wireframe.
//==================================================================

// Par�metro do efeito (vari�vel global no shader)
uniform extern float4x4 gWVP;

// Estrutura
struct OutputVS
{
      float4 posH : POSITION0;
	  float4 color : COLOR0;
};

// Vertex shader
OutputVS TransformVS(float3 posL : POSITION0, float4 inColor : COLOR0)
{
      // Zeramos a estrutura
      OutputVS outVS = (OutputVS)0;

      // Transforma no espa�o de coordenadas homog�neo
      outVS.posH = mul(float4(posL, 1.0f), gWVP);
	  outVS.color = inColor;

      return outVS;
}

// Pixel shader: Retorna nossa cor favorita.
float4 TransformPS(float4 inColor : COLOR0) : COLOR
{	
    return inColor;
}

technique TransformTech
{
      pass P0
      {
            // Especifica o vertex e pixel shader associado a essa passada.            
            vertexShader = compile vs_2_0 TransformVS();
            pixelShader  = compile ps_2_0 TransformPS();

			//Especifica o device state associado a essa passada.
            FillMode = Solid;
      }
}