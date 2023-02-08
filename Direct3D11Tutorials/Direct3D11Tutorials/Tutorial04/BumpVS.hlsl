cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
    float4 mLightPos;
    float4 mLightCol;
    float3 mEyePos;
}

struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 Norm : NORMAL;
    float2 Tex : TEXCOORD;
    float3 Tang : TANGENT;
    float3 Binorm : BINORMAL;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
    float3 Norm : TEXCOORD1;
    float3 ViewDirInTang : TEXCOORD2;
    float3 LightDirInTang : TEXCOORD3;
};

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul(input.Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);

    output.Norm = input.Norm;
    output.Tex = input.Tex;

    float3 viewDirW = mEyePos - input.Pos.xyz;
    float3 lightDirW = mLightPos.xyz - input.Pos.xyz;

    float3 N = normalize(input.Norm);
    float3 T = normalize(input.Tang);
    float3 B = normalize(input.Binorm);

    float3x3 mat2Tang = float3x3(T, B, N);

    output.ViewDirInTang = mul(mat2Tang, viewDirW);
    output.LightDirInTang = lightDirW;//mul(mat2Tang, lightDirW);

    return output;
}