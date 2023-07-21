--====== EX. 1

--Sa se creeze un trigger, trg_update_prod_cascada, asupra tabelei Produse, prin care, la modificarea valorii id_produs din tabela parinte, aceasta sa se modifice automat si in inregistrarile corespondente din tabela copil

-- (update in cascada parinte-copil)

--Sa se verifice declansatorul!

create or replace trigger trg_update_prod_cascada 
after update of id_produs on produse for each row
begin

  update RAND_COMENZI set ID_PRODUS=:new.id_produs where ID_PRODUS=:old.id_produs;

end;
/

SELECT * from PRODUSE;
select * from RAND_COMENZI where ID_PRODUS=1797;

UPDATE PRODUSE set ID_PRODUS= 9999 where ID_PRODUS=1797;

select * from RAND_COMENZI where ID_PRODUS=9999;


--====== EX. 2

-- Sa se creeze un declanşator, trg_stop_marire, care să împiedice mărirea salariului pentru angajații cu vechimea mai mare de 10 de ani.

-- Testați declanșarea trigger-ului.

create or replace trigger trg_stop_marire 
before update of SALARIUL on ANGAJATI for each row
BEGIN

  if (:NEW.salariul > :OLD.salariul and ROUND( (SYSDATE - :OLD.data_angajare)/365 ) >= 10) THEN
    raise_application_error(-20001, 'Nu se poate mari salariul angajatului');
  end if;

END;
/

select * from ANGAJATI where ROUND( (SYSDATE - data_angajare)/365 ) = 10;

UPDATE ANGAJATI SET SALARIUL = SALARIUL + 1 where ID_ANGAJAT = 108;

--====== EX. 3

---Să se adauge în tabela Produse coloana Stoc. Să se introducă valoarea 200 în coloana nou adăugată.

---Să se creeze un trigger, trg_verifica_stoc, care să nu permită comandarea unui produs în cantitate mai mare decât stocul aferent.

---Totodată, pentru produsele comandate, prin trigger se va diminua stocul cu valoarea comandată.

--Să se verifice declanșatorul.

alter table produse add (
  Stoc NUMBER DEFAULT 200
);

create or replace trigger trg_verifica_stoc 
before insert on RAND_COMENZI for each row
DECLARE
  v_stoc PRODUSE.Stoc%TYPE;
begin 
  select stoc into v_stoc from produse where ID_PRODUS = :new.id_produs;
  if (:new.cantitate > v_stoc) then
    raise_application_error(-20002, 'Cantitatea depaseste stocul');
  end if;
  update produse set stoc = stoc - :new.cantitate where ID_PRODUS = :new.id_produs;
end;
/

insert into comenzi values (9999, SYSDATE, 'online', 235, 1, 100);

insert into RAND_COMENZI VALUES (9999, 9999, 20 ,200);

SELECT * from PRODUSE where ID_PRODUS = 9999;

--====== EX. 4

--Sa se creeze un declansator, trg_actualizeaza_istoric, prin care:

-- in momentul modificarii functiei unui angajat, se va adauga automat o noua inregistrare in tabela istoric_functii, astfel:

  ---daca angajatul nu si-a mai schimbat functia niciodata: data de inceput in functia schimbata va fi data angajarii, iar cea de sfarsit data curenta

  ---daca angajatul si-a mai schimbat functia: data de inceput pentru functia schimbata va fi ultima data de sfarsit pe o functie detinuta de angajatul in cauza

-- in momentul stergerii unui angajat, se vor sterge automat toate referirile la angajatul respectiv din tabela istoric_functii

--Sa se verifice declansatorul.

create or replace trigger trg_actualizeaza_istoric after delete or update of ID_FUNCTIE on ANGAJATI for each ROW
DECLARE
  v_check NUMBER;
  v_data_incepere DATE;
BEGIN
  CASE
    WHEN UPDATING THEN
      select count(ID_ANGAJAT) INTO v_check FROM ISTORIC_FUNCTII where ID_ANGAJAT = :OLD.ID_ANGAJAT;
      if (v_check = 0) THEN
        INSERT INTO ISTORIC_FUNCTII VALUES (:OLD.ID_ANGAJAT, :OLD.data_angajare, SYSDATE, :OLD.ID_FUNCTIE, :OLD.ID_DEPARTAMENT);
      ELSE
        SELECT MAX(DATA_SFARSIT) into v_data_incepere FROM ISTORIC_FUNCTII where ID_ANGAJAT = :OLD.ID_ANGAJAT;
        INSERT INTO ISTORIC_FUNCTII VALUES (:OLD.ID_ANGAJAT, v_data_incepere, SYSDATE, :OLD.ID_FUNCTIE, :OLD.ID_DEPARTAMENT);
      END IF;
    WHEN DELETING THEN
      DELETE FROM ISTORIC_FUNCTII WHERE ID_ANGAJAT = :OLD.ID_ANGAJAT;
  END CASE;
  
end;
/

SELECT
  *
FROM
  ANGAJATI;

SELECT * FROM ISTORIC_FUNCTII WHERE ID_ANGAJAT = 206;

UPDATE ANGAJATI SET ID_FUNCTIE = 'AD_VP' WHERE ID_ANGAJAT = 206;

SELECT * FROM ISTORIC_FUNCTII WHERE ID_ANGAJAT = 206;

DELETE FROM ANGAJATI WHERE ID_ANGAJAT = 206;