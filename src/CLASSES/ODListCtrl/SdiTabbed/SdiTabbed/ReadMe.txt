================================================================================
    BIBLIOTHÈQUE MICROSOFT FOUNDATION CLASS : Vue d'ensemble du projet SdiTabbed
===============================================================================

L'Assistant Application a créé cette application SdiTabbed pour  
vous.  Cette application décrit les principes de base de l'utilisation de  
Microsoft Foundation Classes et vous permet de créer votre application.

Ce fichier contient un résumé du contenu de chacun des fichiers qui 
constituent votre application SdiTabbed.

SdiTabbed.vcproj
    Il s'agit du fichier projet principal pour les projets VC++ générés à l'aide 
d'un Assistant Application. 
    Il contient les informations sur la version de Visual C++ qui a généré le 
fichier et  
    des informations sur les plates-formes, configurations et fonctionnalités du 
projet sélectionnées avec 
    l'Assistant Application.

SdiTabbed.h
    Il s'agit du fichier d'en-tête principal de l'application.  Il contient 
d'autres 
    en-têtes de projet spécifiques et déclare la classe d'application CSdiTabbedApp.

SdiTabbed.cpp
    Il s'agit du fichier source principal de l'application qui contient la 
    classe d'application CSdiTabbedApp.


SdiTabbedppc.rc
    Il s'agit du fichier de ressources principal qui répertorie toutes les 
ressources Microsoft Windows 
    que le projet utilise lors de la compilation pour la plate-forme Pocket PC 
ou une 
    plate-forme qui prend en charge le même modèle d'interface utilisateur.  Il 
comprend les icônes 
    les bitmaps et les curseurs qui sont stockés dans le sous-répertoire RES.  
Ce fichier peut être  
modifié directement dans Microsoft Visual C++. Vos ressources de projet sont 
dans 
    1036. Quand le fichier .rc est persistant, les définitions de la 
section des données sont enregistrées 
    comme versions hexadécimales des valeurs numériques qui les définissent au 
lieu  
    du nom convivial de la définition.

res\SdiTabbedppc.rc2
    Ce fichier contient les ressources qui ne sont pas modifiées par Microsoft  
    Visual C++. Vous devez placer toutes les ressources non modifiables par 
    l'éditeur de ressources dans ce fichier.


res\SdiTabbed.ico
    Il s'agit d'un fichier icône, qui est utilisé comme icône de l'application.  
Cette 
    icône est incluse par le fichier de ressource principal.


/////////////////////////////////////////////////////////////////////////////

Pour la fenêtre frame principale :
    Le projet comprend une interface MFC standard.

MainFrm.h, MainFrm.cpp
    Ces fichiers contiennent la classe de frame CMainFrame, qui 
est dérivée de CFrameWnd et contrôle toutes les fonctionnalités de frame SDI.


/////////////////////////////////////////////////////////////////////////////

L'Assistant Application crée un type de document et une vue :

SdiTabbedDoc.h, SdiTabbedDoc.cpp - le document
    Ces fichiers contiennent votre classe CSdiTabbedDoc.  Modifiez ces 
fichiers pour 
    ajouter les données de document spéciales et implémenter l'enregistrement et 
le 
    chargement des fichiers (via CSdiTabbedDoc::Serialize).

SdiTabbedView.h, SdiTabbedView.cpp - la vue du document
    Ces fichiers contiennent votre classe CSdiTabbedView.
    Les objets CSdiTabbedView servent à afficher les objets CSdiTabbedDoc.




/////////////////////////////////////////////////////////////////////////////

Autres fichiers standard :

StdAfx.h, StdAfx.cpp
    Ces fichiers sont utilisés pour générer un fichier d'en-tête précompilé 
(PCH) 
    nommé SdiTabbed.pch et un fichier de types précompilés nommé 
StdAfx.obj.

Resourceppc.h
    Il s'agit du ficher d'en-tête standard, qui définit les nouveaux ID de 
ressources.
    Microsoft Visual C++ lit et met à jour ce fichier.

/////////////////////////////////////////////////////////////////////////////

Autres remarques :

L'Assistant Application utilise "TODO:" pour indiquer les parties du code source 
où vous devrez ajouter ou modifier du code.

Si votre application utilise les MFC dans une DLL partagée et que sa langue  
n'est pas celle du système d'exploitation, vous devez copier le fichier des  
ressources localisées MFC90XXX.DLL correspondant à votre langue dans le 
répertoire de votre application  ("XXX" désigne ici l'abréviation de la langue.  
Par exemple,  
le fichier MFC90DEU.DLL contient des ressources traduites en allemand.)  Si vous 
oubliez de le faire, 
certains éléments de l'interface utilisateur de votre application resteront dans 
la langue du système d'exploitation.

/////////////////////////////////////////////////////////////////////////////
