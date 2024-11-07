Процедура CreateLog(Path, Name, Level, Message) Экспорт
	
	LogTXT = Новый ТекстовыйДокумент;
	LogTXT.УстановитьТекст(Строка(Level) + ":" 
	+ Символы.ПС 
	+ Message);
	LogTXT.Записать(PathManager.AcquirePath(ПредопределенноеЗначение("Перечисление.Paths.logs")) + Name, КодировкаТекста.UTF8);
	
КонецПроцедуры 

Функция CreateLogName(Level) Экспорт
	Возврат "log_" + Формат(ТекущаяДата(), "ДФ=yyyyMMddЧЧммсс") + "_" + Строка(НРег(Строка(Level))) + ".txt";	
КонецФункции

