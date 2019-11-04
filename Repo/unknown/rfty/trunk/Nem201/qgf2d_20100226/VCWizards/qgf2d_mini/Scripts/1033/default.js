
function OnFinish(selProj, selObj)
{
	try
	{
		var strProjectPath = wizard.FindSymbol('PROJECT_PATH');
		var strProjectName = wizard.FindSymbol('PROJECT_NAME');

		selProj = CreateCustomProject(strProjectName, strProjectPath);
		AddConfig(selProj, strProjectName);
		AddFilters(selProj);

		var InfFile = CreateCustomInfFile();
		AddFilesToCustomProj(selProj, strProjectName, strProjectPath, InfFile);
		PchSettings(selProj);
		InfFile.Delete();

		selProj.Object.Save();
	}
	catch(e)
	{
		if (e.description.length != 0)
			SetErrorInfo(e);
		return e.number
	}
}

function CreateCustomProject(strProjectName, strProjectPath)
{
	try
	{
		var strProjTemplatePath = wizard.FindSymbol('PROJECT_TEMPLATE_PATH');
		var strProjTemplate = '';
		strProjTemplate = strProjTemplatePath + '\\default.vcproj';

		var Solution = dte.Solution;
		var strSolutionName = "";
		if (wizard.FindSymbol("CLOSE_SOLUTION"))
		{
			Solution.Close();
			strSolutionName = wizard.FindSymbol("VS_SOLUTION_NAME");
			if (strSolutionName.length)
			{
				var strSolutionPath = strProjectPath.substr(0, strProjectPath.length - strProjectName.length);
				Solution.Create(strSolutionPath, strSolutionName);
			}
		}

		var strProjectNameWithExt = '';
		strProjectNameWithExt = strProjectName + '.vcproj';

		var oTarget = wizard.FindSymbol("TARGET");
		var prj;
		if (wizard.FindSymbol("WIZARD_TYPE") == vsWizardAddSubProject)  // vsWizardAddSubProject
		{
			var prjItem = oTarget.AddFromTemplate(strProjTemplate, strProjectNameWithExt);
			prj = prjItem.SubProject;
		}
		else
		{
			prj = oTarget.AddFromTemplate(strProjTemplate, strProjectPath, strProjectNameWithExt);
		}
		return prj;
	}
	catch(e)
	{
		throw e;
	}
}

function AddFilters(proj)
{
	try
	{
		// Add the folders to your project
		var strSrcFilter = wizard.FindSymbol('SOURCE_FILTER');
		var group;
		group = proj.Object.AddFilter('Source Files');
		group.Filter = "cpp";
		group = proj.Object.AddFilter('Header Files');
		group.Filter = "h";
		group = proj.Object.AddFilter('Resources Files');
		group.Filter = "ico;rc";
	}
	catch(e)
	{
		throw e;
	}
}

function AddConfig(proj, strProjectName)
{
	try
	{
		var config;
		var CLTool;
		var LinkTool;
		
		// Debug ---------------------------------------------------------------------------
		config = proj.Object.Configurations('Debug');
		config.IntermediateDirectory = '$(SolutionDir)/temp/$(ProjectName)/$(ConfigurationName)';
		config.OutputDirectory = '$(SolutionDir)/temp/$(ProjectName)/$(ConfigurationName)';

		CLTool = config.Tools('VCCLCompilerTool');
		CLTool.AdditionalIncludeDirectories = '$(SolutionDir)/components/include';
        CLTool.ProgramDataBaseFileName="$(SolutionDir)/bin/$(ProjectName)-d.pdb";
        CLTool.DebugInformationFormat="4";
		CLTool.RuntimeLibrary = runtimeLibraryOption.rtMultiThreadedDebugDLL;
		CLTool.Optimization = optimizeOption.optimizeDisabled;
        
        LinkTool = config.Tools('VCLinkerTool');
		LinkTool.AdditionalDependencies="sfml-system-s-d.lib sfml-window-s-d.lib sfml-graphics-s-d.lib sfml-audio-s-d.lib sfml-network-s-d.lib qgf2dutil-d.lib box2d-d.lib";
        LinkTool.OutputFile="$(SolutionDir)/bin/$(ProjectName)-d.exe";
        LinkTool.AdditionalLibraryDirectories="$(SolutionDir)/lib/$(ConfigurationName);$(SolutionDir)/lib";
        LinkTool.GenerateDebugInformation="true";
        LinkTool.ProgramDatabaseFile="$(SolutionDir)/bin/$(ProjectName)-d.pdb"
        LinkTool.SubSystem = subSystemOption.subSystemConsole;
        
		// Release ---------------------------------------------------------------------------
		config = proj.Object.Configurations('Release');
		config.IntermediateDirectory = '$(SolutionDir)/temp/$(ProjectName)/$(ConfigurationName)';
		config.OutputDirectory = '$(SolutionDir)/temp/$(ProjectName)/$(ConfigurationName)';

		CLTool = config.Tools('VCCLCompilerTool');
		CLTool.AdditionalIncludeDirectories = '$(SolutionDir)/components/include';
		CLTool.RuntimeLibrary = runtimeLibraryOption.rtMultiThreadedDLL;
        CLTool.Optimization = optimizeOption.optimizeFull;

		LinkTool = config.Tools('VCLinkerTool');
		LinkTool.AdditionalDependencies="sfml-system-s.lib sfml-window-s.lib sfml-graphics-s.lib sfml-audio-s.lib sfml-network-s.lib qgf2dutil.lib box2d.lib";
        LinkTool.OutputFile="$(SolutionDir)/bin/$(ProjectName).exe";
        LinkTool.AdditionalLibraryDirectories="$(SolutionDir)/lib/$(ConfigurationName);$(SolutionDir)/lib";
        LinkTool.SubSystem = subSystemOption.subSystemConsole;

	}
	catch(e)
	{
		throw e;
	}
}

function PchSettings(proj)
{
	// TODO: specify pch settings
}

function DelFile(fso, strWizTempFile)
{
	try
	{
		if (fso.FileExists(strWizTempFile))
		{
			var tmpFile = fso.GetFile(strWizTempFile);
			tmpFile.Delete();
		}
	}
	catch(e)
	{
		throw e;
	}
}

function CreateCustomInfFile()
{
	try
	{
		var fso, TemplatesFolder, TemplateFiles, strTemplate;
		fso = new ActiveXObject('Scripting.FileSystemObject');

		var TemporaryFolder = 2;
		var tfolder = fso.GetSpecialFolder(TemporaryFolder);
		var strTempFolder = tfolder.Drive + '\\' + tfolder.Name;

		var strWizTempFile = strTempFolder + "\\" + fso.GetTempName();

		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');
		var strInfFile = strTemplatePath + '\\Templates.inf';
		wizard.RenderTemplate(strInfFile, strWizTempFile);

		var WizTempFile = fso.GetFile(strWizTempFile);
		return WizTempFile;
	}
	catch(e)
	{
		throw e;
	}
}

function GetTargetName(strName, strProjectName)
{
	try
	{
		// TODO: set the name of the rendered file based on the template filename
		var strTarget = strName;

		if (strName == 'readme.txt')
			strTarget = 'ReadMe.txt';
		if (strName == 'mini.cpp')
		  strTarget = strProjectName+".cpp"

		if (strName == 'sample.txt')
			strTarget = 'Sample.txt';
		if (strName.substr(strName.length-2) == ".h" && strName != "resource.h")
		    strTarget = "include/"+strName;
		if (strName.substr(strName.length-4) == ".cpp")
		    strTarget = "src/"+strName;
		if (strName.substr(strName.length-4) == ".ico")
		    strTarget = "res/"+strName;
		if (strName.substr(strName.length-3) == ".rc")
		    strTarget = "res/"+strName;
		if (strName == "resource.h")
		    strTarget = "res/"+strName;

		return strTarget; 
	}
	catch(e)
	{
		throw e;
	}
}

function AddFilesToCustomProj(proj, strProjectName, strProjectPath, InfFile)
{
	try
	{
		var projItems = proj.ProjectItems

		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');

		var strTpl = '';
		var strName = '';

		var strTextStream = InfFile.OpenAsTextStream(1, -2);
		while (!strTextStream.AtEndOfStream)
		{
			strTpl = strTextStream.ReadLine();
			if (strTpl != '')
			{
				strName = strTpl;
				var strTarget = GetTargetName(strName, strProjectName);
				var strTemplate = strTemplatePath + '\\' + strTpl;
				var strFile = strProjectPath + '\\' + strTarget;

				var bCopyOnly = false;  //"true" will only copy the file from strTemplate to strTarget without rendering/adding to the project
				var strExt = strName.substr(strName.lastIndexOf("."));
				if(strExt==".bmp" || strExt==".ico" || strExt==".gif" || strExt==".rtf" || strExt==".css")
					bCopyOnly = true;
				wizard.RenderTemplate(strTemplate, strFile, bCopyOnly);
				proj.Object.AddFile(strFile);
			}
		}
		strTextStream.Close();
	}
	catch(e)
	{
		throw e;
	}
}