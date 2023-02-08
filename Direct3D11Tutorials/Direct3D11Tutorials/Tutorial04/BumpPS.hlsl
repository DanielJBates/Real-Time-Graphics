cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
    float4 mLightPos;
    float4 mLightCol;
    float3 mEyePos;
}

Texture2D txStoneColor : register(t0);
Texture2D txStoneBump : register(t1);
SamplerState txStoneSampler : register(s0);

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
    float3 Norm : TEXCOORD1;
    float3 ViewDirInTang : TEXCOORD2;
    float3 LightDirInTang : TEXCOORD3;
};


float4 main(PS_INPUT input) : SV_Target
{
    float4 Color = 0;

    float4 stoneCol = txStoneColor.Sample(txStoneSampler, input.Tex);
    float4 stoneNormal = txStoneBump.Sample(txStoneSampler, input.Tex);
    float3 N = normalize(2.0 * stoneNormal.xyz - 1.0);

    float diff = max(0.0f, dot(input.LightDirInTang, N));

    Color = stoneCol * diff;

    return Color;
}