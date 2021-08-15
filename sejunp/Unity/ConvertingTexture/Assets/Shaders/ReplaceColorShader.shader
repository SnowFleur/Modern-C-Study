Shader "Custom/ReplaceColorShader"
{
	Properties
	{
		_MainTex("Texture", 2D) = "white" {}
		_ReplaceTex("Replace Texture", 2D) = "white" {}
		_TargetColor("TargetColor", Color) = (0, 0, 0, 1)
		_Margin("Margin", float) = 0.0
		[Toggle(USE_Replace_Color)] _UseReplaceColor("Use Replace Color", Float) = 1
		[Toggle(USE_Replace_Alpha)] _UseCombineAlpha("Use Replace Alpha", Float) = 1
		[Toggle(USE_Only_Target_Color)] _UseOnlyTargetColor("Use Only Target Color", Float) = 0
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

				#pragma shader_feature USE_Replace_Color
				#pragma shader_feature USE_Replace_Alpha
				#pragma shader_feature USE_Only_Target_Color

				sampler2D _MainTex, _ReplaceTex;
				float4 _MainTex_ST;
				float4 _TargetColor;
				float _Margin;

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
					half4 color2 = tex2D(_ReplaceTex, i.uv);
					half4 result = half4(0, 0, 0, 1);

#ifdef USE_Only_Target_Color
					if (length(color1.rgb - _TargetColor.rgb) > _Margin)
						return color1;
#endif // USE_Only_Target_Color

	#ifdef USE_Replace_Color
					result.rgb = color2.rgb;
	#else // USE_Replace_Color
					result.rgb = color1.rgb;
	#endif // USE_Replace_Color
	#ifdef USE_Replace_Alpha
					result.a = color2.a;
	#else // USE_Replace_Alpha
					result.a = color1.a;
	#endif // USE_Replace_Alpha

					return result;
				}

				ENDCG
			}
		}
}
