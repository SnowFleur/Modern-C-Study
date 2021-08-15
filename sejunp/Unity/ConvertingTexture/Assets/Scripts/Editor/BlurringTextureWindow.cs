using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.IO;

public class BlurringTextureWindow : BakeTextureWindow
{
    protected static int Iterations = 1;
    protected static Material FilterMaterial;
    protected static float UpSamplingDelta = 1.0f;
    protected static float DownSamplingDelta = 1.0f;

    private Vector2Int SavedResolution;

    [MenuItem("Tools/Bake material to texture/Blurring Texture")]
    static void OpenWindow()
    {
        // create window
        BakeTextureWindow NewWindow = EditorWindow.GetWindow<BlurringTextureWindow>();
        NewWindow.Show();
    }

    protected override void UpdateGUI()
    {
        base.UpdateGUI();

        // dispaly GUI in window
        Iterations = EditorGUILayout.IntField("Iterations", Iterations);
        FilterMaterial = (Material)EditorGUILayout.ObjectField("Filter Material", FilterMaterial, typeof(Material), false);
        UpSamplingDelta = EditorGUILayout.FloatField("UpSamplingDelta", UpSamplingDelta);
        DownSamplingDelta = EditorGUILayout.FloatField("DownSamplingDelta", DownSamplingDelta);
    }

    protected override void CheckVariables()
    {
        base.CheckVariables();

        Iterations = Mathf.Clamp(Iterations, 1, 16);
    }

    protected override void ReadyToBake()
    {
        base.ReadyToBake();

        SavedResolution = Resolution;
    }

    protected override void BakeTexture()
    {
        // copy texture to rendertexture
        RenderTexture CurrentSource = RenderTexture.GetTemporary(Resolution.x, Resolution.y);
        BlitTexture(bUseTargetTextureAsSource ? TargetTexture : null, CurrentSource, ImageMaterial);

        if(FilterMaterial != null)
        {
            FilterMaterial.SetFloat("_Delta", DownSamplingDelta);
        }

        // iterate downsampling
        for (int i = 0; i < Iterations && Resolution.x > 0 && Resolution.y > 0; ++i)
        {
            Resolution /= 2;
            RenderTexture CurrentDestination = RenderTexture.GetTemporary(Resolution.x, Resolution.y);
            BlitTexture(CurrentSource, CurrentDestination, FilterMaterial);
            RenderTexture.ReleaseTemporary(CurrentSource);
            CurrentSource = CurrentDestination;
        }

        if (FilterMaterial != null)
        {
            FilterMaterial.SetFloat("_Delta", UpSamplingDelta);
        }

        // iteracte upsampling
        for (int i = 0; i < Iterations; ++i)
        {
            Resolution *= 2;
            RenderTexture CurrentDestination = RenderTexture.GetTemporary(Resolution.x, Resolution.y);
            BlitTexture(CurrentSource, CurrentDestination, FilterMaterial);
            RenderTexture.ReleaseTemporary(CurrentSource);
            CurrentSource = CurrentDestination;
        }

        // transfer image from rendertexture to texture2d
        Texture2D NewTexture = new Texture2D(Resolution.x, Resolution.y);
        RenderTexture.active = CurrentSource;
        NewTexture.ReadPixels(new Rect(Vector2.zero, Resolution), 0, 0);

        // save texture to file
        byte[] image = EncodeTexture(NewTexture, EncodeType);
        if (image != null)
        {
            File.WriteAllBytes(GetAllFilePath(), image);
        }
        AssetDatabase.Refresh();

        // clean up textures
        RenderTexture.active = null;
        RenderTexture.ReleaseTemporary(CurrentSource);
        DestroyImmediate(NewTexture);
    }

    protected override void EndBake()
    {
        base.ReadyToBake();

        // restore resolution
        Resolution = SavedResolution;
    }
}
