#include "ComponentList.h"

ComponentList::ComponentList( QWidget* parent ) :
		QListWidget(parent), m_uniqueIDCounter(0) {
	connect(this, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
	        this, SLOT(changeItem(QListWidgetItem*,QListWidgetItem*)) );
}

ComponentList::~ComponentList() {
}

unsigned int ComponentList::addComponent( std::string displayedName ) {
	return this->addNewItem( displayedName );
}

unsigned int ComponentList::addNewItem( std::string displayedName ) {
    const QString label = QString::fromStdString( displayedName );
	QListWidgetItem* newItem = new QListWidgetItem( label, this );
	newItem->setData(Qt::UserRole, m_uniqueIDCounter);

    this->addItem( newItem );

//	emit itemChanged( m_uniqueIDCounter );

	return m_uniqueIDCounter++;
}

void ComponentList::deleteItem( unsigned int itemID ) {
	int candidate = -1;
	for( int i = 0; i < this->count(); i++ ) {
		if( (this->item(i)->data(Qt::UserRole).toUInt()) == itemID ) {
			candidate = i;
		}
	}
	if( candidate != -1 ) {
		QListWidgetItem* tmpItem = takeItem(candidate); // TODO: Bug here? (try to delete last item in list...)
		delete tmpItem;
//		emit itemDeleted( itemID );
	}
}

void ComponentList::changeItem( QListWidgetItem* current, QListWidgetItem* previous ) {
	if( current ) {
		unsigned int ID = current->data(Qt::UserRole).toUInt();
		emit selectionChanged( ID );
	}
	else {
		emit selectionChanged( -1 );
	}
}

void ComponentList::selectItem( unsigned int itemID ) {
	for( int i = 0; i < count(); i++ ) {
		if( item(i)->data(Qt::UserRole).toUInt() == itemID ) {
			setCurrentItem(item(i));
		}
	}
}

void ComponentList::deleteButtonPressed() {
	deleteCurrentComponent();
}

void ComponentList::deleteCurrentComponent() {
	emit deleteCurrent( currentItem()->text().toStdString() );
}
