--1. t_company
-- зарегистрированный работодатель
CREATE TABLE t_company
(
	i_company INTEGER PRIMARY KEY ASC,		--ключ
	x_company VARCHAR(128),					--название организации
	dt_create DATE,							--дата открытия
	dt_close DATE							--дата закрытия
);
CREATE UNIQUE INDEX pk_company ON t_company (i_company ASC);

--2. t_department
-- подразделение
CREATE TABLE t_department
(
	i_department	INTEGER PRIMARY KEY ASC,	--ключ
	x_department	VARCHAR(256)				--название отдела
);
CREATE UNIQUE INDEX pk_department ON t_department (i_department ASC);
CREATE INDEX idx_department ON t_department (x_department ASC);

--3. t_jobplace
-- место работы
CREATE TABLE t_jobplace
(
	i_jobplace		INTEGER PRIMARY KEY ASC,	--ключ
	i_company		INTEGER,					--ключ компании
	i_department	INTEGER						--ключ отдела
);
CREATE UNIQUE INDEX pk_jobplace ON t_jobplace (i_jobplace ASC);
CREATE INDEX idx_jobplace_company ON t_jobplace (i_company ASC);
CREATE INDEX idx_jobplace_department ON t_jobplace (i_department ASC);

--4. t_employee
-- сотрудник
CREATE TABLE t_employee
(
	i_employee		INTEGER PRIMARY KEY ASC,	--ключ
	x_employee		VARCHAR(128)				--ФИО
);
CREATE UNIQUE INDEX pk_employee ON t_employee (i_employee ASC);
CREATE UNIQUE INDEX idx_employee ON t_employee (x_employee ASC);

--5. t_employee_job_period
-- период занятости сотрудника
CREATE TABLE t_employee_job_period
(
	i_employee		INTEGER,					--ключ
	i_jobplace		INTEGER,					--ключ места работы
	dt_begin		DATE,						--дата начала работы
	dt_end			DATE						--дата увольнения
);
CREATE UNIQUE INDEX pk_employee_job_period ON t_employee_job_period (i_employee ASC, i_jobplace ASC, dt_begin ASC, dt_end ASC );

--6. t_employee_vacation_period
-- период отпуска сотрудника
CREATE TABLE t_employee_vacation_period
(
	i_employee		INTEGER,					--ключ
	dt_begin		DATE,						--дата начала отпуска
	dt_end			DATE						--дата окончания отпуска
);
CREATE UNIQUE INDEX pk_employee_vacation_period ON t_employee_vacation_period (i_employee ASC, dt_begin ASC, dt_end ASC );

--7. t_state_date
-- официальные государственные даты
CREATE TABLE t_state_date
(
	n_year			INTEGER,					--год
	n_date_type		SMALLINT,					--тип даты(0 - рабочий день, 1 - выходной)
	dt_date			DATE						--дата
);
CREATE UNIQUE INDEX pk_state_date ON t_state_date (n_year ASC, n_date_type ASC, dt_date ASC );

