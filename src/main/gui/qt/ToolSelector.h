#ifndef TOOLSELECTOR_H
#define TOOLSELECTOR_H

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QGridLayout>
#include <QStackedWidget>
#include <string>

#include "Component.h"
#include "Tool.h"
#include "../../gui/Drawable2D.h"
#include "../RenderItem3D.h"

/** @brief This class manages the tool-selection process of Happah
 * 
 * For this purpose, this class provides the selection widget itself 
 * and a widget for more elaborated tool settings.
 */
class ToolSelector: public QWidget {
Q_OBJECT

public:
	ToolSelector(QWidget* parent);

	~ToolSelector();

	/** @brief Adds new tool to tool selector.
	 *
	 * This function adds a new entry to the tool selector and its widgets.
	 * @param toolButton Button that will be shown in the selector widget.
	 *    This button will be resized to fit into the grid.
	 * @param toolSettings Widget which will be shown when this tool was
	 *    selected by the user.
	 */
	void addTool(Tool* tool);

	/** @brief Returns settings dialog widget.
	 *
	 * @return Widget which shows tool-settings-widget of the currently
	 *    selected tool. To be placed somewhere in the application.
	 */
	QWidget* getSettingsWidget();

private:
	int m_toolCount; /**< Number of registered tools. */
	int m_currToolID; /**< Identifies currently selected tool. */
	static const int BUTTONS_PER_ROW = 4; /**< Number of tools per row in selector widget. */

	QGridLayout* m_selectorGrid; /**< Local layout for selection buttons. */
	QButtonGroup* m_buttonGroup; /**< Handles click events of tool selection. */
	QStackedWidget* m_settingsWidgetStack; /**< Widget to display tool settings. */
	QList<Tool*> m_toolList; /**< List of registered tools. */

private slots:
	void toolSelected(int toolID);
//	void newComponent(Component* component);
	void newComponent(Drawable2D* drawable);
	void newComponent(RenderItem3D* renderItem);
	void update();
	void deleteComponent();

public slots:
	void leftClickAt( QPointF point );
	void rightClickAt( QPointF point );
	void finalise( std::string name );

signals:
//	void emitComponent(std::string name);
	void emitDrawable(Drawable2D* drawable);
	void emitDrawable(RenderItem3D* renderItem);
	void changed();
	void deleteCurrentComponent();
};

#endif
