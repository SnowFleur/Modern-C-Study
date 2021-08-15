// BoxSampling에 대해 https://catlikecoding.com/unity/tutorials/advanced-rendering/bloom/ 참고
Shader "Custom/BoxSamplingShader"
{
	Properties
	{
		_MainTex("Texture", 2D) = "white" {}
		_Delta("Delta", Range(0, 1)) = 1.0
	}

	CGINCLUDE
	#include "UnityCG.cginc"

	sampler2D _MainTex;
	float4 _MainTex_ST;
	float4 _MainTex_TexelSize;
	float _Delta;

	half3 SampleBox(float2 uv, float delta)
	{
		float4 o = _MainTex_TexelSize.xyxy * float2(-delta, delta).xxyy;
		half3 s = tex2D(_MainTex, uv + o.xy).rgb + tex2D(_MainTex, uv + o.zy).rgb
			+ tex2D(_MainTex, uv + o.xw).rgb + tex2D(_MainTex, uv + o.zw).rgb;
		return s * 0.25f;
	}

	//the object data that's put into the vertex shader
	struct appdata
	{
		float4 vertex : POSITION;
		float2 uv : TEXCOORD0;
	};

	//the data that's used to generate fragments and can be read by the fragment shader
	struct v2f
	{
		float4 position : SV_POSITION;
		float2 uv : TEXCOORD0;
	};

	v2f vert(appdata v)
	{
		v2f o;

		//convert the vertex positions from object space to clip space so they can be rendered
		o.position = UnityObjectToClipPos(v.vertex);
		o.uv = TRANSFORM_TEX(v.uv, _MainTex);
		return o;
	}
	ENDCG

	SubShader
	{
		//the material is completely non-transparent and is rendered at the same time as the other opaque geometry
		Tags{ "RenderType" = "Opaque" "Queue" = "Geometry"}
		Cull Off
		ZTest Always
		ZWrite Off

		Pass
		{
			CGPROGRAM
			#include "UnityCG.cginc"

			#pragma vertex vert
			#pragma fragment frag

			half4 frag(v2f i) : SV_TARGET
			{
				return half4(SampleBox(i.uv, _Delta), 1);
			}
			ENDCG
		}
	}
}
