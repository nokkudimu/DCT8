Функция AcquirePath(Path) Экспорт
	Если Path = ПредопределенноеЗначение("Перечисление.Paths.infoBase") Тогда
		Возврат "/home/nokkudimu/repos/tekken8_data_collector/infoBase/";
	ИначеЕсли Path = ПредопределенноеЗначение("Перечисление.Paths.logs") Тогда 
		Возврат "/home/nokkudimu/repos/tekken8_data_collector/logs/";
	ИначеЕсли Path = ПредопределенноеЗначение("Перечисление.Paths.shellScripts") Тогда  
		Возврат "/home/nokkudimu/repos/tekken8_data_collector/shellScripts/";
	ИначеЕсли Path = ПредопределенноеЗначение("Перечисление.Paths.temporaryFiles") Тогда   
		Возврат "/home/nokkudimu/repos/tekken8_data_collector/temporaryFiles/";
	ИначеЕсли Path = ПредопределенноеЗначение("Перечисление.Paths.vzlom") Тогда 
		Возврат "/home/nokkudimu/repos/tekken8_data_collector/vzlom/";
	// ...	
	КонецЕсли;
КонецФункции