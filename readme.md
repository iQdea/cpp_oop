+ В тестах несколько банков
+ В банках счета и клиенты
+ Клиент: имя, фамиилия (обязательно); адрес; номер паспорта
+ Каждый счет принадлежит клиенту
+ Счета: дебетовый, депозитный, кредитный
* Дебетовый
	+ обычный с фиксированным процентом
	+ Начисление процента
	+ Нельзя уходить в минус
	+ Коммиссий нет
* Депозит
	+ Срок депозита
	+ Нельзя снимать и переводить, пока не закончится срок
	+ Можно пополнять
	+ Процент зависит от начальной суммы
	+ Комиссий нет
* Кредит
	+ Кредитный лимит
	+ Проверка на максимальный минус
	+ Процент на остаток отсутствует
	+ Фиксированная комиссия, пока в минусе
+ Процент на остаток начисляется ежедневно
+ Процент выплачивается раз в месяц
+ Механизм снятия, пополнения и перевода
+ Идентификаторы счетов
+ Клиент создается по шагам
+ Сомнительный счет у клиента без адреса или паспорта
+ Запрещены операции снятия и перевода выше указанной суммы для сомнительного счета
+ Механизм дат в тестах
+ Отмена мошенеческих транзакций
+ Правильное создание счетов (фабрика должна читать банковские данные)
