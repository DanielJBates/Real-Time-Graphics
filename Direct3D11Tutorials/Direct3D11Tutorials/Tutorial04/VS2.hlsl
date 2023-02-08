cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
    float4 LightPos[2];
    float4 LightCol[2];
    float3 EyePos;
}

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
    float3 Norm : TEXCOORD0;
};

//struct VS_OUTPUT
//{
//    float4 Pos : SV_POSITION;
//    float3 Norm : TEXCOORD0;
//    float3 PosWorld : TEXCOORD1;
//};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------

VS_OUTPUT VS_main(float4 Pos : POSITION, float4 Color : COLOR, float3 Norm : NORMAL)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Pos = mul(Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);

    if (Norm.z == -1.0f)
    {
        output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);
    }
    else if (Norm.z == 1.0f)
    {
        output.Color = float4(0.4f, 0.1f, 0.7f, 1.0f);
    }
    else if (Norm.y == -1.0f)
    {
        output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);
    }
    else if (Norm.y == 1.0f)
    {
        output.Color = float4(0.0f, 1.0f, 0.0f, 1.0f);
    }
    else if (Norm.x == -1.0f)
    {
        output.Color = float4(1.0f, 0.0f, 0.0f, 1.0f);
    }
    else if (Norm.x == 1.0f)
    {
        output.Color = float4(1.0f, 0.5f, 0.5f, 1.0f);
    }
    
    return output;
}

//VS_OUTPUT VS_main(float4 Pos : POSITION, float4 Color : COLOR, float3 Normal : NORMAL)
//{
//    VS_OUTPUT output = (VS_OUTPUT)0;
//    float4 inPos = Pos;
//
//    float3 translation = float3(1.0f, 0.3f, 1.0f);
//    float3 scale = float3(0.2f, 3.0f, 3.0f);
//
//    float angle = 1.5708;
//
//    float3x3 rotationMatrix = { cos(angle), 0.0f, sin(angle),
//                               0.0f, 1.0f, 0.0f,
//                               -sin(angle), 0.0f, cos(angle) };
//
//
//    inPos.xyz = (scale * (mul(inPos.xyz, rotationMatrix))) + translation;
//
//    output.Pos = mul(inPos, World);
//    output.Pos = mul(output.Pos, View);
//    output.Pos = mul(output.Pos, Projection);
//    output.Color = Color;
//    return output;
//}

//VS_OUTPUT VS_main(float4 Pos : POSITION, float4 Color : COLOR, float3 Normal : NORMAL)
//{
//    VS_OUTPUT output = (VS_OUTPUT)0;
//    output.Pos = mul(Pos, World);
//    output.Pos = mul(output.Pos, View);
//    output.Pos = mul(output.Pos, Projection);
//
//    float4 materialAmb = float4(0.1f, 0.2f, 0.3f, 1.0f);
//    float4 materialDif = float4(1.0f, 0.0f, 0.0f, 1.0f);
//    float4 lightCol = float4(1.0f, 0.6f, 0.8f, 1.0f);
//    float3 lightDir = normalize(LightPos.xyz - Pos.xyz);
//    float3 normal = normalize(Normal);
//    float diff = max(0.0f, dot(lightDir, normal));
//
//    output.Color = (materialAmb + diff * materialDif) * lightCol;
//    return output;
//}

//VS_OUTPUT VS_main(float4 Pos : POSITION, float3 Normal : NORMAL)
//{
//    VS_OUTPUT output = (VS_OUTPUT)0;
//    output.Pos = mul(Pos, World);
//    output.Pos = mul(output.Pos, View);
//    output.Pos = mul(output.Pos, Projection);
//
//    output.PosWorld = Pos.xyz;
//    output.Norm = Normal.xyz;  
//
//    return output;
//}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

//float4 PS( VS_OUTPUT input ) : SV_Target
//{
//    return input.Color;
//}
//
//float4 PS_Red(VS_OUTPUT input) : SV_Target
//{
//	float4 finalColour = 0;
//
//	float4 materialAmb = float4(0.1f, 0.2f, 0.3f, 1.0f);
//	float4 materialDif = float4(1.0f, 0.0f, 0.0f, 1.0f);
//	float4 materialSpec = float4(1.0f, 1.0f, 1.0f, 1.0f);
//
//
//	for (int i = 0; i < 2; i++)
//	{
//	    float3 lightDir = normalize(LightPos[i].xyz - input.PosWorld.xyz);
//
//		float3 normal = normalize(input.Norm);
//
//		float diff = max(0.0f, dot(lightDir, normal));
//
//
//		float3 R = reflect(-lightDir, normal);
//		float3 V = normalize(EyePos - input.PosWorld.xyz);
//		float spec = pow(max(0.0, dot(V, R)), 100);
//
//
//		finalColour += (0.2f * materialAmb) + (diff * materialDif) + (spec * materialSpec) * LightCol[i];
//	}
//
//	finalColour.a = 1;
//
//	return  finalColour;
//}
//
//float4 PS_Green(VS_OUTPUT input) : SV_Target
//{
//    float4 finalColour = 0;
//
//    float4 materialAmb = float4(0.0f, 0.2f, 0.3f, 1.0f);
//    float4 materialDif = float4(0.0f, 1.0f, 0.0f, 1.0f);
//    float4 materialSpec = float4(1.0f, 1.0f, 1.0f, 1.0f);
//
//
//    for (int i = 0; i < 2; i++)
//    {
//        float3 lightDir = normalize(LightPos[i].xyz - input.PosWorld.xyz);
//        float3 normal = normalize(input.Norm);
//
//        float diff = max(0.0f, dot(lightDir, normal));
//
//
//        float3 R = reflect(-lightDir, normal);
//        float3 V = normalize(EyePos - input.PosWorld.xyz);
//        float spec = pow(max(0.0, dot(V, R)), 10);
//
//
//        finalColour += (0.2f * materialAmb) + (diff * materialDif) + (spec * materialSpec) * LightCol[i];
//    }
//
//
//    finalColour.a = 1;
//
//    return  finalColour;
//}
//
//float4 PS_Blue(VS_OUTPUT input) : SV_Target
//{
//   float4 finalColour = 0;
//
//    float4 materialAmb = float4(0.0f, 0.2f, 0.3f, 1.0f);
//    float4 materialDif = float4(0.0f, 0.0f, 1.0f, 1.0f);
//    float4 materialSpec = float4(1.0f, 1.0f, 1.0f, 1.0f);
//
//
//    for (int i = 0; i < 2; i++)
//    {
//        float3 lightDir = normalize(LightPos[i].xyz - input.PosWorld.xyz);
//        float3 normal = normalize(input.Norm);
//
//        float diff = max(0.0f, dot(lightDir, normal));
//
//
//        float3 R = reflect(-lightDir, normal);
//        float3 V = normalize(EyePos - input.PosWorld.xyz);
//        float spec = pow(max(0.0, dot(V, R)), 200);
//
//
//        finalColour += (0.2f * materialAmb) + (diff * materialDif) + (spec * materialSpec) * LightCol[i];
//    }
//
//
//    finalColour.a = 1;
//
//    return  finalColour;
//}

//float4 PS(VS_OUTPUT input) : SV_Target
//{
//    float4 finalColour = 0;
//
//    float4 materialAmb = float4(0.0f, 0.2f, 0.3f, 1.0f);
//    float4 materialDif = float4(1.0f, 0.0f, 0.0f, 1.0f);
//    float4 materialSpec = float4(1.0f, 1.0f, 1.0f, 1.0f);
//
//
//    for (int i = 0; i < 2; i++)
//    {
//		float3 lightDir = normalize(LightPos[i].xyz - input.PosWorld.xyz);
//		float3 normal = normalize(input.Norm);
//
//		float diff = max(0.0f, dot(lightDir, normal));
//
//
//		float3 R = reflect(-lightDir, normal);
//		float3 V = normalize(EyePos - input.PosWorld.xyz);
//		float spec = pow(max(0.0, dot(V, R)), 30);
//
//
//		finalColour += (0.5f * materialAmb) + (diff * materialDif) + (spec * materialSpec) * LightCol[i];
//    }
//   
//
//    finalColour.a = 1;
//
//    return  finalColour;
//}

