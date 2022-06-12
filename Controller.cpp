#include "Controller.h"
#include <QDebug>
void Controller::readInput() {
    if ( inputIndex < input_.size() ){
        char c = input_[inputIndex];
        ++inputIndex;
        memory.set_value(c);
    }
}

void Controller::writeOutput() {
//    qDebug() << memory.get_current_value();
    output_->moveCursor (QTextCursor::End);
    output_->insertPlainText (QString(memory.get_current_value()));
    output_->moveCursor (QTextCursor::End);
}
