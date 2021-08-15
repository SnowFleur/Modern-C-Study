// https://www.ronja-tutorials.com/post/030-baking-shaders/ Âü°í
Shader "Custom/3DDefaultShader"
{
    Properties
    {
        _Height ("Height", Range(0,1)) = 0
        _Color ("BaseColor", Color) = (0, 0, 0, 1)
        _MainTex ("Texture", 3D) = "white" {}
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

			sampler3D _MainTex;
			float4 _MainTex_ST;
			fixed4 _Color;
			float _Height;

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
				half4 color = tex3D(_MainTex, float3(i.uv, _Height));
				color = _Color;
				return color;
			}

			ENDCG
		}
    }
}
