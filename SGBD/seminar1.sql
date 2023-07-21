-- SET SERVEROUTPUT ON
VAR g_numar NUMBER;
DECLARE
  v_nr NUMBER(6,2);
  v_data DATE:=SYSDATE;
  v_data2 TIMESTAMP:=SYSTIMESTAMP;
  v_de_la_consola VARCHAR2(20):='&&ceva_de_la_tastatura'; -- daca pui && se citeste o singura data de la tastatura same as an accept
BEGIN
  v_nr:=123.456;
  DBMS_OUTPUT.PUT_LINE('Variabila este ' || v_nr);
  DBMS_OUTPUT.PUT_LINE(ADD_MONTHS(v_data, 2));
  DBMS_OUTPUT.PUT_LINE(TO_CHAR(v_data, 'DD-MON-YYYY HH:Mi:SS'));
  DBMS_OUTPUT.PUT_LINE(v_data2);
  DBMS_OUTPUT.PUT_LINE(v_de_la_consola || '&ceva_de_la_tastatura');
  :g_numar:=TRUNC(v_nr);
  DBMS_OUTPUT.PUT_LINE(:g_numar);
END;
/
select * from ANGAJATI where ID_ANGAJAT = :g_numar;
DECLARE
  v_total ANGAJATI.SALARIUL%TYPE;
  n_angajat ANGAJATI.NUME%TYPE;
  v_angajat NUMBER;
  id ANGAJATI.ID_ANGAJAT%TYPE :=&id;
BEGIN
  SELECT SALARIUL + (SALARIUL * NVL(COMISION, 0)), NUME, ROUND((SYSDATE-DATA_ANGAJARE)/365) INTO v_total, n_angajat, v_angajat FROM ANGAJATI WHERE ID_ANGAJAT = id;
  DBMS_OUTPUT.PUT_LINE(id || ' ' || n_angajat || ' ' || v_total || ' ' || v_angajat);
END;
/
-- sa se mareasca salariul angajatului citit de la tastatura
DECLARE
  v_salariu ANGAJATI.SALARIUL%TYPE;
  v_id ANGAJATI.ID_ANGAJAT%TYPE := &id;
  v_res ANGAJATI.SALARIUL%TYPE;
BEGIN
  SELECT SALARIUL INTO v_salariu FROM ANGAJATI WHERE ID_ANGAJAT = v_id;
  v_salariu := v_salariu + 100;
  UPDATE ANGAJATI SET SALARIUL= v_salariu WHERE ID_ANGAJAT = v_id RETURNING SALARIUL INTO v_res;
  DBMS_OUTPUT.PUT_LINE(v_res);
END;
/
SELECT SALARIUL FROM ANGAJATI WHERE ID_ANGAJAT = 100;
-- UPDATE ANGAJATI SET SALARIUL = 24000 WHERE ID_ANGAJAT= 100;
-- transcript ora
-- select-urile trebuie sa returneze o valoare daca sunt in cadrul unui bloc PL/SQL