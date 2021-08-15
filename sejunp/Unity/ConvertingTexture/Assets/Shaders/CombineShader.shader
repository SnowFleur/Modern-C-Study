Shader "Custom/CombineShader"
{
	Properties
	{
		_MainTex("Texture", 2D) = "white" {}
		_CombineTex("Combine Texture", 2D) = "white" {}
		[Toggle(USE_Combine_Color)] _UseCombineColor("Use Combine Color", Float) = 1
		[Toggle(USE_Combine_Alpha)] _UseCombineAlpha("Use Combine Alpha", Float) = 1
	}

	SubShader
	{
		//the material is completely non-transparent and is rendered at the same time as the other opaque geometry
		Tags{ "RenderType" = "Opaque" "Queue" = "Geometry"}

		Pass
		{
			Blend One One

			CGPROGRAM
			#include "UnityCG.cginc"

			#pragma vertex vert
			#pragma fragment frag

			#pragma shader_feature USE_Combine_Color
			#pragma shader_feature USE_Combine_Alpha

			sampler2D _MainTex, _CombineTex;
			float4 _MainTex_ST;

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

			half4 frag(v2f i) : SV_TARGET
			{
				half4 color1 = tex2D(_MainTex, i.uv);
				half4 color2 = tex2D(_CombineTex, i.uv);
				half4 result = half4(0, 0, 0, 1);

#ifdef USE_Combine_Color
				result.rgb = color1.rgb + color2.rgb;
#else // USE_Combine_Color
				result.rgb = color1.rgb;
#endif // USE_Combine_Color
#ifdef USE_Combine_Alpha
				result.a = color1.a + color2.a;
#else // USE_Combine_Alpha
				result.a = color1.a;
#endif // USE_Combine_Alpha

				return result;
			}

			ENDCG
		}
	}
}
