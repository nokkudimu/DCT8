&НаКлиенте
Асинх Процедура CollectTekken8Data() Экспорт
	//checking if processes are active
	Promise = ЗапуститьПриложениеАсинх("/home/nokkudimu/repos/tekken8_data_collector/shellScripts/checkProcess.sh", , Истина);
	Result = Ждать Promise;
	Попытка
		Если Result = 0 Тогда
		JSON_info = JSONCommands.ReadJSONFile("/home/nokkudimu/repos/tekken8_data_collector/temporaryFiles/processIsLaunched.json"); 	
		КонецЕсли;
	Исключение 
		// creating log files in specific folder if something goes wrong	
	КонецПопытки;
КонецПроцедуры
