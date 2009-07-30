/*
	� Murielle Descerisiers, 2009
	murielle.descerisiers@gmail.com

	Ce logiciel est un programme informatique d�velopp� au Qu�bec et servant �
	consulter le dictionnaire de la langue fran�aise d'�mile Littr�.

	Ce logiciel est r�gi par la licence CeCILL soumise au droit fran�ais et respectant
	les principes de diffusion des logiciels libres. Vous pouvez utiliser, modifier et/ou
	redistribuer ce programme sous les conditions de la licence CeCILL telle que diffus�e
	par le CEA, le CNRS et l'INRIA sur le site http://www.cecill.info.

	En contrepartie de l'accessibilit� au code source et des droits de copie, de
	modification et de redistribution accord�s par cette licence, il n'est offert aux
	utilisateurs qu'une garantie limit�e. Pour les m�mes raisons, seule une
	responsabilit� restreinte p�se sur l'auteur du programme, le titulaire des droits
	patrimoniaux et les conc�dants successifs.

	� cet �gard l'attention de l'utilisateur est attir�e sur les risques associ�s au
	chargement, � l'utilisation, � la modification et/ou au d�veloppement et � la
	reproduction du logiciel par l'utilisateur �tant donn� sa sp�cificit� de logiciel
	libre, qui peut le rendre complexe � manipuler et qui le r�serve donc � des
	d�veloppeurs et des professionnels avertis poss�dant des connaissances informatiques
	approfondies. Les utilisateurs sont donc invit�s � charger et tester l'ad�quation du
	logiciel � leurs besoins dans des conditions permettant d'assurer la s�curit� de
	leurs syst�mes et ou de leurs donn�es et, plus g�n�ralement, � l'utiliser et
	l'exploiter dans les m�mes conditions de s�curit�.

	Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez pris
	connaissance de la licence CeCILL, et que vous en avez accept� les termes.
*/

#include <QApplication>
#include <QTranslator>
#include <QFontDatabase>

#include "classestyle.h"
#include "classeprincipale.h"

QString AjouterBarreOblique(const QString &texteChemin)
{
	return texteChemin.endsWith(QDir::separator()) ? texteChemin
		: texteChemin + QDir::separator();
}

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);
	application.setStyle(new classeStyle);


	QFileInfo fichier("Littre.qm");
	QString texteRepertoire(fichier.exists()
			? AjouterBarreOblique(fichier.absolutePath())
			: AjouterBarreOblique(application.applicationDirPath()));

	QString texteTitre(QString::fromUtf8("Dictionnaire le Littr\303\251"));
	bool boolRemiseANeuf(false);

	for(int nombreArgument = 0; nombreArgument < argc; ++nombreArgument) {
		if(QString(argv[nombreArgument]) == "--titre" && nombreArgument < (argc - 1))
			texteTitre = QString::fromLocal8Bit(argv[nombreArgument + 1]);
		else if(QString(argv[nombreArgument]) == "--repertoire"
				&& nombreArgument < (argc - 1))
			texteRepertoire = AjouterBarreOblique(
					QString::fromLocal8Bit(argv[nombreArgument + 1]));
		else if(QString(argv[nombreArgument]) == "--remise-a-neuf")
			boolRemiseANeuf = true;
	}

	QTranslator traducteur;
	if (traducteur.load("Littre", texteRepertoire) == false) {
		QMessageBox::warning(0, texteTitre, "Impossible d'ouvrir le fichier "
				+ texteRepertoire + QString::fromUtf8("Littre.qm. L'applic"
				"ation ne peut d\303\251marrer sans ce fichier."));
		return 0;
	}
	application.installTranslator(&traducteur);

	QResource::registerResource(texteRepertoire + "Littre-Index.dat");

	QStringList listeFichiersPolice;
	listeFichiersPolice << "DejaVuSerif.ttf" << "DejaVuSerif-Bold.ttf"
			<< "DejaVuSerif-Italic.ttf" << "DejaVuSerif-BoldItalic.ttf";
	for (QStringList::const_iterator iterateurPolice = listeFichiersPolice.constBegin();
			iterateurPolice != listeFichiersPolice.constEnd(); ++iterateurPolice) {
		QFile fichier(":/" + *iterateurPolice);
		if (fichier.open(QIODevice::ReadOnly))
			QFontDatabase::addApplicationFontFromData(fichier.readAll());
	}
	application.setFont(QFont("DejaVu Serif", 10));

	classePrincipale fenetrePrincipale(texteRepertoire, texteTitre, boolRemiseANeuf);
	fenetrePrincipale.show();
	return application.exec();
}
