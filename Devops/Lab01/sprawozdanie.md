## Kacper Suder 408408
---
Sprawozdanie numer 1 - Git, Gałęzie, SSH, Docker
---
1. Przed pierwszymi zajęciami zainstalowano klienta Git:
<p align="center">
	<img src="../zrzutyEkranu/Lab1/1.png/" alt="wersja gita">
</p>
2. Sklonowano repozytorium przy użyciu html:
<p align="center">
	<img src="../zrzutyEkranu/Lab1/2.png" alt="Sklonowanie repozytorium przez HTML">
</p>
3. Utworzono klucze ssh z opcją -f tworzącą go w aktualnie znajdującej się lokalizacji:
<p align="center">
	<img src="../zrzutyEkranu/Lab1/3.png" alt="Generowane kluczy ssh z -f">
</p>

- w celu poprawności połączenia należało dodać identyfikator. Następnie sprawdzono poprawność połączenia:
<p align="center">
	<img src="../zrzutyEkranu/Lab1/4.png" alt="Dodanie identyfikatora i sprawdzenie poprawności połączenia">
</p>

4. Wygenerwano kolejne klucze, tym razem bez opcji -f. Zostały one zapisane w katalogu home/nazwa_użytkownika/.ssh, gdzie nazwa_użytkownika jest nazwą użytkownika generującego klucz. Dodano nowo wygenerowany klucz publiczny do Githuba:
<p align="center">
	<img src="../zrzutyEkranu/Lab1/5.png" alt="Generowane kluczy ssh do katalogu domyślnego">
</p>

- następnie sprawdzono poprawność połączenia z GitHub-em:
<p align="center">
	<img src="../zrzutyEkranu/Lab1/6.png" alt="Sprawdzenie poprawności połączenia z GitHub-em">
</p>

5. Skopiowano repozytorium przy użyciu SSH:
<p align="center">
	<img src="../zrzutyEkranu/Lab1/7.png" alt="Kopiowanie repozytorium przez SSH">
</p>

6. Utworzono i przełączono się na własną gałąź pod nazwą "KS408408", przy użyciu komendy "git checkout -b KS408408":
<p align="center">
	<img src="../zrzutyEkranu/Lab1/8.png" alt="Własna gałąź">
</p>

7. We właściwym katalogu dla grupy utworzono nowy katalog o nazwie "KS408408":
<p align="center">
	<img src="../zrzutyEkranu/Lab1/9.png" alt="Nowy katalog - "twoje_iniciały_&_nr_indexu">
</p>

8. Napisano Git hook'a - Skrypt weryfikujący, czy każdy commit zaczyna się od "KS408408":
<p align="center">
	<img src="../zrzutyEkranu/Lab1/10.png" alt="Git Hook">
</p>

- W celu poprawnego działania, należało skopiować z katalogu ".git/hooks" przykładowy "commit-msg.sample" do katalogu "KS408408". Następnie edytowano plik w wyżej wymieniony sposób i zmieniono nazwę pliku w katalogu GCL6/KS408408 na commit-msg. Kopię pliku dodano do katalogu ".git/hooks".

10. Sprawdzono poprawność działania Git Hooka:
<p align="center">
        <img src="../zrzutyEkranu/Lab1/12.png" alt="Sprawdzanie poprawności Git Hook-a">
</p>

11. Utworzono plik ze sprawozdaniem i dodano zrzuty ekranu. Następnie wysłano aktualizację do zdalnego źródła:
<p align="center">
	<img src="../zrzutyEkranu/Lab1/11.png" alt="Dodanie aktualizacji do zdalnego źródła">
</p>

12. Kolejne laboratoria rozpoczęto od dodania do konta na GitHubie uwierzetelnienia dwuetapowego:
<p align="center">
        <img src="../zrzutyEkranu/Lab2/1.png" alt="Dodanie uwierzetlnienia">
</p>

13. Utworzono konto oraz zapoznano się z przykładowymi obrazami na DockerHubie:
<p align="center">
        <img src="../zrzutyEkranu/Lab2/5.png" alt="Zalogowano się do DockerHub-a">
</p>

14. Zainstalowano Dockera przy pomocy komendy "dnf install docker" podanego podczas zajęć przez prowadzącego (Dockera zainstalowano wcześniej, przy pomocy wcześniej wspomnianej komendy):
<p align="center">
        <img src="../zrzutyEkranu/Lab2/6.png" alt="Instalacja Docker-a">
</p>

15.  Pobrano następujace obrazy:
---
	* hello-world:
<p align="center">
        <img src="../zrzutyEkranu/Lab2/HelloWorld.png" alt="Hello-world">
</p>
	- Jak można zauważyć, Docker symulowany jest przez Podman-a, co nie ma jednak wpływu na jego działanie

---

	* busybox:

<p align="center">
        <img src="../zrzutyEkranu/Lab2/2.png" alt="busybox 1">
</p>

	- Uruchomiono busyboxa i sprawdzono efekt działania:
<p align="center">
        <img src="../zrzutyEkranu/Lab2/3,1.png" alt="Busybox">
</p>

	- Podłączono się interaktywnie do kontenera i wywołano numeru sesji:
<p align="center">
        <img src="../zrzutyEkranu/Lab2/4.png" alt="busybox interaktywnie">
</p>

---

	* mysql:
<p align="center">
        <img src="../zrzutyEkranu/Lab2/mysql.png" alt="mysql">
</p>
 <p align="center">
        <img src="../zrzutyEkranu/Lab2/mysql2.png" alt="mysql">
</p>
<p align="center">
        <img src="../zrzutyEkranu/Lab2/mysql3.png" alt="mysql">
</p>

---

	* Ubuntu:
	-Pobrano i uruchomiono obrazu Ubuntu:
<p align="center">
        <img src="../zrzutyEkranu/Lab2/ubuntu1.png" alt="Obraz ubunty">
</p>

	- PID1 w kontenerze:
<p align="center">
        <img src="../zrzutyEkranu/Lab2/PID1.png" alt="PID1">
</p>
	
	- Procesy dockera na hoście:
<p align="center">
        <img src="../zrzutyEkranu/Lab2/ProcesyDoc.png" alt="Procesy dockera">
</p>

	- Aktualizacja pakietów:
<p align="center">
        <img src="../zrzutyEkranu/Lab2/aktualizacja.png" alt="aktualizacja pakietow">
</p>

	- Opuszczono kontener:
<p align="center">
        <img src="../zrzutyEkranu/Lab2/exit.png" alt="wyjscie z kontenera">
</p>

16. Napisano własny plik Dockerfile:
<p align="center">
        <img src="../zrzutyEkranu/Lab2/Dockerfile.png" alt="dockerfile">
</p>

17. Zbudowano obraz:
<p align="center">
        <img src="../zrzutyEkranu/Lab2/docbud.png" alt="budowa obrazu">
</p>


18. Uruchomiono i sprawdzono poprawność pobrania repozytorium:
<p align="center">
        <img src="../zrzutyEkranu/Lab2/wer.png" alt="weryfikacja">
</p>

19. Wyświetono kontenery:
<p align="center">
        <img src="../zrzutyEkranu/Lab2/kontenery.png" alt="kontenery">
</p>

	- Wszystkie kontenery zostały wcześniej zatrzymane

20. Wyczyszczono obrazy:
<p align="center">
        <img src="../zrzutyEkranu/Lab2/obrazy.png" alt="obrazy">
</p>
<p align="center">
        <img src="../zrzutyEkranu/Lab2/pure.png" alt="czyszczenie">
</p>

21. Wystawiono Pull Request do gałęzi grupowej jako zgłoszenie wykonanego zadania:
</p>
<p align="center">
        <img src="../zrzutyEkranu/Lab2/pull.png" alt="oddanno sprawozdanie">
        <img src="../zrzutyEkranu/Lab2/pull1.png" alt="oddanno sprawozdanie">
</p>



