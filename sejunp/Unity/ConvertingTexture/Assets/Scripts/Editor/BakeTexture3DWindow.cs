using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

// https://www.ronja-tutorials.com/post/030-baking-shaders/ Âü°í
public class BackTexture3DWindow : BakeTextureWindow
{
    protected enum ETextureType
    {
        Texture2D,
        Texture3D,
    };

    protected static int Height;
    protected static ETextureType TextureType;

    private static bool bHasHegiht;

    [MenuItem("Tools/Bake material to texture/Default Texture3D")]
    static void OpenWindow()
    {
        // create window
        BakeTextureWindow NewWindow = EditorWindow.GetWindow<BackTexture3DWindow>();
        NewWindow.Show();
    }

    protected override void UpdateGUI()
    {
        base.UpdateGUI();

        TextureType = (ETextureType)EditorGUILayout.EnumPopup("Texture Type", TextureType);
        Height = EditorGUILayout.IntField("Height", Height);
    }

    protected override void ShowWarnings()
    {
        base.ShowWarnings();

        if (!bHasHegiht)
        {
            EditorGUILayout.HelpBox("Please set height a size bigger than zero", MessageType.Warning);
        }
    }

    protected override void CheckVariables()
    {
        base.CheckVariables();

        bHasHegiht = (Height > 0);
    }

    protected override bool IsEnabled()
    {
        return base.IsEnabled() && bHasHegiht;
    }

    protected override void BakeTexture()
    {
        // get rendertexture to render layers to and texture3d to save values to as well as 2d texture for transferring data
        RenderTexture NewRenderTexture = RenderTexture.GetTemporary(Resolution.x, Resolution.y);
        Texture3D NewVolumeTexture = new Texture3D(Resolution.x, Resolution.y, Height, TextureFormat.ARGB32, false);
        Texture2D TempTexture = new Texture2D(Resolution.x, Resolution.y);

        // calculate voxel amounts and pixel amounts
        RenderTexture.active = NewRenderTexture;
        int VoxelAmount = Resolution.x * Resolution.y * Height;
        int SlicePixelAmount = Resolution.x * Resolution.y;
        Color32[] Colors = new Color32[VoxelAmount];

        // loop through slices and write them to 3d texture
        for (int Slice = 0; Slice < Height; ++Slice)
        {
            // hit the middle of the voxles
            float Z = (Slice + 0.5f) / Height;
            ImageMaterial.SetFloat("_Height", Z);

            // transfer image from rendertexture to color32 array
            Graphics.Blit(null, NewRenderTexture, ImageMaterial);
            TempTexture.ReadPixels(new Rect(0, 0, Resolution.x, Resolution.y), 0, 0);
            Color32[] SliceColors = TempTexture.GetPixels32();

            // copy the content of colors
            int SliceBaseIndex = Slice * SlicePixelAmount;
            for (int Pixel = 0; Pixel < SlicePixelAmount; ++Pixel)
            {
                Colors[SliceBaseIndex + Pixel] = SliceColors[Pixel];
            }
        }

        // apply and save 3d texture
        NewVolumeTexture.SetPixels32(Colors);
        AssetDatabase.CreateAsset(NewVolumeTexture, GetAllFilePath());

        //clean up variables
        RenderTexture.active = null;
        RenderTexture.ReleaseTemporary(NewRenderTexture);
        DestroyImmediate(NewVolumeTexture);
        DestroyImmediate(TempTexture);
    }

    protected override bool ShouldCheckMaterial()
    {
        return true;
    }
}