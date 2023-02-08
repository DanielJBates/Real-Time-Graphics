//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
    float4 LightPosition[2];
    float4 LightColour[2];
    float3 EyePosition;
}

Texture2D txColour: register(t0);
SamplerState txSampler : register(s0);

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 Norm : NORMAL;
    float2 Tex : TEXCOORD;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : TEXCOORD0;
    float2 Tex : TEXCOORD1;
    float3 PosWorld : TEXCOORD2;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul( input.Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
    output.Norm = input.Norm.xyz;
    output.Tex = input.Tex;
    output.PosWorld = input.Pos;
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
    float4 colour;
    float4 txtColour = txColour.SampleLevel(txSampler, input.Tex, 0);
    
    for (int i = 0; i < 2; i++)
    {
        float3 lightDir = normalize(LightPosition[i].xyz - input.PosWorld.xyz);
        float3 normal = normalize(input.Norm);

        float diff = max(0.0f, dot(lightDir, normal));

        float3 R = reflect(-lightDir, normal);
        float3 V = normalize(EyePosition - input.PosWorld.xyz);
        float spec = pow(max(0.0, dot(V, R)), 100);

        if (i == 1)
        {
            diff = diff * 0.2f;
        }

        colour += (0.2f * txtColour) + (diff * txtColour) + (spec * txtColour) * (LightColour[i] * 0.2f);
    }
        colour.a = 1.0f;
        return colour;
}

//float4 PS(PS_INPUT input) : SV_Target
//{
//    float4 txtColor = txColor.SampleLevel(txSampler, input.Tex, 0);
//
//    float3 lightDir = normalize(LightPosition.xyz - input.PosWorld.xyz);
//    float3 normal = normalize(input.Norm);
//
//    float diff = max(0.0f, dot(lightDir, normal));
//
//    float4 colour = (0.2f * txtColor) * (diff * txtColor) * LightColour;
//}
