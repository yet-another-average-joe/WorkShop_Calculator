================================================================================
    BIBLIOTH�QUE MICROSOFT FOUNDATION CLASS : Vue d'ensemble du projet StockCalc
===============================================================================

L'Assistant Application a cr�� cette application StockCalc pour  
vous.  Cette application d�crit les principes de base de l'utilisation de  
Microsoft Foundation Classes et vous permet de cr�er votre application.

Ce fichier contient un r�sum� du contenu de chacun des fichiers qui 
constituent votre application StockCalc.

StockCalc.vcproj
    Il s'agit du fichier projet principal pour les projets VC++ g�n�r�s � l'aide 
d'un Assistant Application. 
    Il contient les informations sur la version de Visual C++ qui a g�n�r� le 
fichier et  
    des informations sur les plates-formes, configurations et fonctionnalit�s du 
projet s�lectionn�es avec 
    l'Assistant Application.

StockCalc.h
    Il s'agit du fichier d'en-t�te principal de l'application.  Il contient 
d'autres 
    en-t�tes de projet sp�cifiques et d�clare la classe d'application CStockCalcApp.

StockCalc.cpp
    Il s'agit du fichier source principal de l'application qui contient la 
    classe d'application CStockCalcApp.


StockCalcppc.rc
    Il s'agit du fichier de ressources principal qui r�pertorie toutes les 
ressources Microsoft Windows 
    que le projet utilise lors de la compilation pour la plate-forme Pocket PC 
ou une 
    plate-forme qui prend en charge le m�me mod�le d'interface utilisateur.  Il 
comprend les ic�nes 
    les bitmaps et les curseurs qui sont stock�s dans le sous-r�pertoire RES.  
Ce fichier peut �tre  
modifi� directement dans Microsoft Visual C++. Vos ressources de projet sont 
dans 
    1036. Quand le fichier .rc est persistant, les d�finitions de la 
section des donn�es sont enregistr�es 
    comme versions hexad�cimales des valeurs num�riques qui les d�finissent au 
lieu  
    du nom convivial de la d�finition.

res\StockCalcppc.rc2
    Ce fichier contient les ressources qui ne sont pas modifi�es par Microsoft  
    Visual C++. Vous devez placer toutes les ressources non modifiables par 
    l'�diteur de ressources dans ce fichier.


res\StockCalc.ico
    Il s'agit d'un fichier ic�ne, qui est utilis� comme ic�ne de l'application.  
Cette 
    ic�ne est incluse par le fichier de ressource principal.


/////////////////////////////////////////////////////////////////////////////

L'Assistant Application cr�e une classe de bo�te de dialogue :

StockCalcDlg.h, StockCalcDlg.cpp � la bo�te de dialogue
    Ces fichiers contiennent votre classe CStockCalcDlg.  Cette classe 
d�finit 
    le comportement de la bo�te de dialogue principale de votre application.  Le 
mod�le de bo�te de dialogue se trouve 
    dans le fichier de ressources principal, qui peut �tre modifi� dans 
Microsoft Visual C++.


/////////////////////////////////////////////////////////////////////////////

Autres fichiers standard :

StdAfx.h, StdAfx.cpp
    Ces fichiers sont utilis�s pour g�n�rer un fichier d'en-t�te pr�compil� 
(PCH) 
    nomm� StockCalc.pch et un fichier de types pr�compil�s nomm� 
StdAfx.obj.

Resourceppc.h
    Il s'agit du ficher d'en-t�te standard, qui d�finit les nouveaux ID de 
ressources.
    Microsoft Visual C++ lit et met � jour ce fichier.

/////////////////////////////////////////////////////////////////////////////

Autres remarques :

L'Assistant Application utilise "TODO:" pour indiquer les parties du code source 
o� vous devrez ajouter ou modifier du code.

Si votre application utilise les MFC dans une DLL partag�e et que sa langue  
n'est pas celle du syst�me d'exploitation, vous devez copier le fichier des  
ressources localis�es MFC90XXX.DLL correspondant � votre langue dans le 
r�pertoire de votre application  ("XXX" d�signe ici l'abr�viation de la langue.  
Par exemple,  
le fichier MFC90DEU.DLL contient des ressources traduites en allemand.)  Si vous 
oubliez de le faire, 
certains �l�ments de l'interface utilisateur de votre application resteront dans 
la langue du syst�me d'exploitation.

/////////////////////////////////////////////////////////////////////////////
