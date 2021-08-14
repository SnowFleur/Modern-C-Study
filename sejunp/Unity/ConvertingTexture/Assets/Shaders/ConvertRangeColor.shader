Shader "Custom/ConvertRangeColor"
{
	Properties
	{
		_TargetColor("TargetColor", Color) = (0, 0, 0, 1)
		_ConvertColor("ConvertColor", Color) = (0, 0, 0, 1)
		_Margin("Margin", float) = 0.0
		[Toggle(USE_Convert_Color)] _UseConvertColor("Use Convert Color", Float) = 0
		[Toggle(USE_Convert_Alpha)] _UseConvertAlpha("Use Convert Alpha", Float) = 0
		_MainTex("Texture", 2D) = "white" {}
	}

		SubShader
	{
		//the material is completely non-transparent and is rendered at the same time as the other opaque geometry
		Tags{ "RenderType" = "Opaque" "Queue" = "Geometry"}

		Pass
		{
			CGPROGRAM
			#include "UnityCG.cginc"

			#pragma vertex vert
			#pragma fragment frag

			#pragma shader_feature USE_Convert_Color
			#pragma shader_feature USE_Convert_Alpha

			sampler2D _MainTex;
			float4 _MainTex_ST;
			float4 _TargetColor;
			float4 _MaxColor;
			float _Margin;

			fixed4 ConvertColor(fixed4 InColor)
			{
				if (length(InColor.rgb - _TargetColor.rgb) <= _Margin)
				{
#ifdef USE_Convert_Color
					InColor.rgb = _TargetColor.rgb;
#endif // USE_Convert_Color
#ifdef USE_Convert_Alpha
					InColor.a = _TargetColor.a;
#endif // USE_Convert_Alpha
				}

				return InColor;
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

			fixed4 frag(v2f i) : SV_TARGET
			{
				fixed4 color = tex2D(_MainTex, i.uv);
				return ConvertColor(color);
			}

			ENDCG
		}
	}
}
