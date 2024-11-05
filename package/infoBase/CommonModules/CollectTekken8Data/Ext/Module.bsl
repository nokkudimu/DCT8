&НаКлиенте
Асинх Процедура CollectTekken8OnlineProwess() Экспорт
	//checking if processes are active
	Promise = ЗапуститьПриложениеАсинх(PathManager.AcquirePath(ПредопределенноеЗначение("Перечисление.Paths.shellScripts")) + "checkProcess.sh", , Истина);
	Result = Ждать Promise;
	Попытка 
		Если Result = 0 Тогда
		JSON_info = JSONCommands.ReadJSONFile("/home/nokkudimu/repos/tekken8_data_collector/temporaryFiles/processIsLaunched.json"); 	
		КонецЕсли;
	Исключение 
		// creating log files in specific folder if something goes wrong
		LogLevel = ПредопределенноеЗначение("Перечисление.LogLevels.Fatal");
		LogOperations.CreateLog(PathManager.AcquirePath(ПредопределенноеЗначение("Перечисление.Paths.logs")),
		LogOperations.CreateLogName(LogLevel),
		LogLevel, 
		ОписаниеОшибки());
	КонецПопытки;
КонецПроцедуры 

&НаКлиенте
Асинх Процедура CollectTekken8OfflineProwess() Экспорт

КонецПроцедуры 

