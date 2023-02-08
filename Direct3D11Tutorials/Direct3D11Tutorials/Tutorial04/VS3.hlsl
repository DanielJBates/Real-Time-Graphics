cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
}

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
    float3 Norm : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------

VS_OUTPUT main(float4 Pos : POSITION, float4 Color : COLOR, float3 Norm : NORMAL)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Pos = mul(Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);

    if (Norm.z == -1.0f)
    {
        output.Color = float4(0.5f, 0.5f, 0.0f, 1.0f);
    }
    else if (Norm.z == 1.0f)
    {
        output.Color = float4(0.5f, 0.0f, 0.5f, 1.0f);
    }
    else if (Norm.y == -1.0f)
    {
        output.Color = float4(0.0f, 0.5f, 0.5f, 1.0f);
    }
    else if (Norm.y == 1.0f)
    {
        output.Color = float4(0.9f, 0.6f, 0.0f, 1.0f);
    }
    else if (Norm.x == -1.0f)
    {
        output.Color = float4(0.6f, 1.0f, 0.2f, 1.0f);
    }
    else if (Norm.x == 1.0f)
    {
        output.Color = float4(1.0f, 0.0f, 1.0f, 1.0f);
    }

    return output;
}