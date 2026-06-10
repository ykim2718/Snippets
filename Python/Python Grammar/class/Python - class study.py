def CpSubPubClass(com_str):
    def return_decorated_class(uClass):
        class CpSubPubEventHandler:
            def OnReceived(self):
                self.usr_obj.publish(self.com_obj)

        class DecoratedCpSubPubClass(uClass):
            def __init__(self, *args, **kwargs):
                handler = type('CpSubPubEventHandler_%s' % id(self),
                               (CpSubPubEventHandler,),
                               {}
                               )
                handler.usr_obj = self
                handler.com_obj = win32com.client.Dispatch(com_str)
                win32com.client.WithEvents(handler.com_obj, handler)
                self.handler = handler
                super(self.__class__, self).__init__(*args, **kwargs)

            def subscribe(self):
                super(self.__class__, self).subscribe(self.handler.com_obj)

        return DecoratedCpSubPubClass

    return return_decorated_class
