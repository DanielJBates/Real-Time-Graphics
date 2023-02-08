cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
}

Texture2D txRockColor : register(t0);
SamplerState txRockSampler : register(s0);

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
    float3 Norm : TEXCOORD1;
};


float4 PS(PS_INPUT input) : SV_Target
{
    float4 Color = txRockColor.SampleLevel(txRockSampler, input.Tex, 0);

    return Color;
}

//float4 PS(PS_INPUT input, bool IsFrontFace : SV_IsFrontFace) : SV_Target
//{
//    float4 color;
//    if (!IsFrontFace) //Behaves oppisite of expected if it is front facing you get a false a ! have been used as a fix
//    {
//        color = txRockColor.SampleLevel(txRockSampler, input.Tex, 0);
//    }
//    else
//    {
//        color = txWoodColor.SampleLevel(txWoodSampler, input.Tex, 0);
//    }
//
//    return color;
//}

