
BASCULER TOUTE LA GESTION DE L'ETAT READ ONLY / TEXTE VIDE de l'edit dans CListBoxUpDown


--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG
Apr�s cr�ation d'un nouveau fichier, lorsqu'on sort du mode �dition, la liste d�roulante "Fichier de donn�es" 
	de l'onglet "Fichier" est vid�e de son contenu. Les fichiers ne sont pas effac�s ! Pour contourner ce bug, 
	en attendant sa correction, il suffit de quitter MatDb, et de le relancer. La liste est alors correctement remplie.
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG
Si on supprime toutes les cat�gories, la derni�re reste affich�e dans l'edit de la page Rechercher
il y a d'autres probl�mes, dus au fait que la nuance et la cat�gorie courantes ne sont pas remis 
� NULL quand ces listes sont vides. Trouver o� faire cette MAJ des pointeurs
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG TULADANLCU
dans une listboxupdown, quand on clique long pour drag & drop, le champ edit associ� devrait �tre mis � jour sur WM_LBTUTTONDOWN
probl�me : la s�lection d'une listbox se fait sur LBUTTONUP !
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
Bug d'affichage lors de l'abandon d'un d�placement par "tap & hold" : la barre d'insertion ne s'efface pas compl�tement.
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
page Rechercher : probl�me de navigation avec la listbox : les fl�ches haut bas font passer le focus ailleurs (perte de focus de la listbox)
-> CEdit remplac� par CEditEx : le CEdit semble ganger le focus si on change son texte par programmation
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG KASTANANAFOUTE
num�rotation des nouvelles nuances : le deuxi�me indice devrait �tre r�actualis� en fonction (pas critique !!!)
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
Si on s�lectionne une cat�gorie dans la page Nuances, le focus de combo est perdu
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
Si on ajoute une nouvelle cat�gorie, le champ d'�dition de nuance n'est pas vide � la page "Nuances" ; idem si on s�lectionne
	une cat�gorie dont la liste de nuances est vide ; donc pb de MAJ de l'edit sur liste de cat�gories vide
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
Si on cr�e une cat�gorie, puis qu'on la supprime : "probl�me li� � gwes.exe"
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
Si on cr�e une nuance alors que aucune cat�gorie n'est cr��e, probl�me : le bouton "+" devrait �tre d�sactiv� si pas de nuance pr�sente
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
Si on supprime une cat�gorie avec nuances alors que c'est la seule : l'edit et la liste dans la page Nuances n'est pas vid�e
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
Si on supprime toutes les cat�gories, l'edit ID n'est pas vid�
--------------------------------------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
Si on cr�e un nouveau fichier, que toutes les pages ont �t� cr��es, qu'on ajoute une cat�gorie, puis qu'on ajoute une nuance
	la liste d'objets nomm�s des nuances n'est pas cr��e ou pass�e � la ListBoxUpDown 
	en revanche pas de probl�me si la page doit �tre cr��e (jamais consult�e)
--------------------------------------------------------------------------------------------------------------------------------------------------------------
	
--------------------------------------------------------------------------------------------------------------------------------------------------------------
BUG CORRIGE
si on passe en mode �dition, l'edit de la page Classes reste � l'�tat "read only" tant qu'on ne s�lectionne pas une cat�gorie
--------------------------------------------------------------------------------------------------------------------------------------------------------------

