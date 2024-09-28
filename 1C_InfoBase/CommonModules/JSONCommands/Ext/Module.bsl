Функция ReadJSONFile(Path) Экспорт
	JSON_proc = Новый ЧтениеJSON;
	JSON_proc.ОткрытьФайл(Path);
	
	Возврат ПрочитатьJSON(JSON_proc, Ложь); 
КонецФункции