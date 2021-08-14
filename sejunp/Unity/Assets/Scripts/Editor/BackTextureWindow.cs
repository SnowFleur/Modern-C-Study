using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.IO;

// https://www.ronja-tutorials.com/post/030-baking-shaders/ Âü°í
public class BakeTextureWindow : EditorWindow
{
    protected enum EEncodeType
    {
        PNG,
        JPG,
        TGA,
        EXR
    };

    protected static Material ImageMaterial;
    protected static string SaveFilePath = "Assets";
    protected static string SaveFileName = "BakdedImage";
    protected static Vector2Int Resolution;
    protected static EEncodeType EncodeType;
    protected static Texture2D SourceTexture;
    protected static Texture2D TargetTexture;
    protected static bool bNoUseMaterial;

    private static bool bHasMaterial;
    private static bool bHasResolution;
    private static bool bHasImageFile;

    [MenuItem("Tools/Bake material to texture/Default Texture2D")]
    static void OpenWindow()
    {
        // create window
        BakeTextureWindow NewWindow = EditorWindow.GetWindow<BakeTextureWindow>();
        NewWindow.Show();
    }

    private void OnGUI()
    {
        EditorGUILayout.HelpBox("Set the material you want to bake as well as the size and location of the texture you want to bake to, then press the \"Bake\" button", MessageType.None);

        using (var Check = new EditorGUI.ChangeCheckScope())
        {
            UpdateGUI();

            if (Check.changed)
            {
                CheckVariables();
            }
        }

        GUI.enabled = IsEnabled();

        // trigger baking
        if (GUILayout.Button("Bake"))
        {
            ReadyToBake();
            BakeTexture();
            EndBake();
        }

        // don't mess with other interfaces
        GUI.enabled = true;

        ShowWarnings();
    }

    protected virtual void UpdateGUI()
    {
        // dispaly GUI in window
        SaveFilePath = ChooseFilePath(SaveFilePath);
        SaveFileName = EditorGUILayout.TextField("File Name", SaveFileName);
        EncodeType = (EEncodeType)EditorGUILayout.EnumPopup("Encode Type", EncodeType);
        ImageMaterial = (Material)EditorGUILayout.ObjectField("Material", ImageMaterial, typeof(Material), false);
        Resolution = EditorGUILayout.Vector2IntField("Resolution", Resolution);
        TargetTexture = (Texture2D)EditorGUILayout.ObjectField("Target Texture", TargetTexture, typeof(Texture2D), false);
        SourceTexture = (Texture2D)EditorGUILayout.ObjectField("Source Texture", SourceTexture, typeof(Texture2D), false);
        bNoUseMaterial = EditorGUILayout.Toggle("No Use Mateterial", bNoUseMaterial);
    }
    
    protected virtual void ShowWarnings()
    {
        if (!bHasResolution)
        {
            EditorGUILayout.HelpBox("Please set resolution a size bigger than zero", MessageType.Warning);
        }

        if (!bHasImageFile)
        {
            EditorGUILayout.HelpBox("No file to save the image to given", MessageType.Warning);
        }
    }

    protected virtual void CheckVariables()
    {
        bHasResolution = (Resolution.x > 0 && Resolution.y > 0);
        bHasImageFile = (!string.IsNullOrEmpty(SaveFilePath) && !string.IsNullOrEmpty(SaveFileName));
    }

    protected virtual bool IsEnabled()
    {
        return bHasResolution && bHasImageFile;
    }

    protected string ChooseFilePath(string InPath)
    {
        // allow the user to enter ouput file both as text or via file browser
        EditorGUILayout.LabelField("File path");
        using (new GUILayout.HorizontalScope())
        {
            InPath = EditorGUILayout.TextField(InPath);
            if(GUILayout.Button("choose path"))
            {
                // set default values for directory, then try to override them with values of existing path
                string DirectoryPath = "Assets/";

                try
                {
                    DirectoryPath = Path.GetDirectoryName(InPath);
                }
                catch(System.ArgumentException e)
                {
                    System.Diagnostics.StackFrame CurrentStackFrame = new System.Diagnostics.StackFrame(true);
                    Debug.LogWarning(CurrentStackFrame.GetMethod().Name + "(" + CurrentStackFrame.GetFileLineNumber().ToString() + ") : " + e.Message);
                }

                DirectoryPath = EditorUtility.SaveFolderPanel("Choose file path", DirectoryPath, DirectoryPath);
                if (!string.IsNullOrEmpty(DirectoryPath))
                {
                    string RelativePath = GetRelativePath(DirectoryPath);
                    if (!string.IsNullOrWhiteSpace(RelativePath))
                    {
                        InPath = RelativePath;
                    }
                    else
                    {
                        Debug.LogWarning("You can only save the file to the relative path");
                    }
                }

                // Repaint editor because the file changed and we can't set it in the textfield retroactively
                Repaint();
            }
        }
        return InPath;
    }

    protected virtual void ReadyToBake()
    {
        if (TargetTexture != null && ImageMaterial != null)
        {
            ImageMaterial.SetTexture("_MainTex", TargetTexture);
        }

        if (!bNoUseMaterial)
        {
            SourceTexture = null;
        }

    }

    protected virtual void BakeTexture()
    {
        // render material to rendertexture
        RenderTexture NewRenderTexture = RenderTexture.GetTemporary(Resolution.x, Resolution.y);

        if(ImageMaterial != null)
        {
            Graphics.Blit(SourceTexture, NewRenderTexture, ImageMaterial);
        }
        else
        {
            Graphics.Blit(SourceTexture, NewRenderTexture);
        }

        // transfer image from rendertexture to texture2d
        Texture2D NewTexture = new Texture2D(Resolution.x, Resolution.y);
        RenderTexture.active = NewRenderTexture;
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
        RenderTexture.ReleaseTemporary(NewRenderTexture);
        DestroyImmediate(NewTexture);
    }

    protected virtual void EndBake()
    {
        if(File.Exists(GetAllFilePath()))
        {
            Debug.Log("Bake texture success");
        }
        else
        {
            Debug.Log("Bake texture failed");
        }
    }

    public string GetAllFilePath()
    {
        return SaveFilePath + "/" + SaveFileName + GetEncodeExtextion(EncodeType);
    }

    static public string GetRelativePath(string InPath)
    {
        return InPath.Substring(InPath.IndexOf("Assets"));
    }

    static protected byte[] EncodeTexture(Texture2D InTexture, EEncodeType InType)
    {
        switch (InType)
        {
            case EEncodeType.PNG:
                return InTexture.EncodeToPNG();
            case EEncodeType.JPG:
                return InTexture.EncodeToJPG();
            case EEncodeType.TGA:
                return InTexture.EncodeToTGA();
            case EEncodeType.EXR:
                return InTexture.EncodeToEXR();
        }

        return null; // invalid value
    }

    static protected string GetEncodeExtextion(EEncodeType InType, bool bOnlyExtentionName = false)
    { 
        switch (InType)
        {
            case EEncodeType.PNG:
                return bOnlyExtentionName ? "png" : ".png";
            case EEncodeType.JPG:
                return bOnlyExtentionName ? "jpg" : ".jpg";
            case EEncodeType.TGA:
                return bOnlyExtentionName ? "tga" : ".tga";
            case EEncodeType.EXR:
                return bOnlyExtentionName ? "exr" : ".exr";
        }

        return ""; // invalid value
    }
}
